#include "server_game.h"

#include <sstream>

#include "easylogging++.h"
#include "c24/c24.h"

using c24::communication::StreamBackendInterface;
using c24::communication::StreamTcpServer;
using c24::communication::ServerStream;
using namespace std;

ServerGame::ServerGame(vector<int> ports)
    : turn_length_milliseconds_(TURN_LENGTH_MILLISECONDS) {
  num_players_ = ports.size();
  ListenForPlayers(ports);
}

bool ServerGame::Authenticate(int pid, string login, string password) {
  return pid >= 0 && !login.empty() && !password.empty();
}

void ServerGame::InitRound() {
  board_size_ = rand() % (MAX_BOARD_SIZE - MIN_BOARD_SIZE + 1) + MIN_BOARD_SIZE;
  board_ = Board<ServerCell>(board_size_);
  for (int i = 0; i < board_size_; ++i) {
    for (int j = 0; j < board_size_; ++j) {
      board_[Pos(i, j)].num_candies = rand() % 5;
      board_[Pos(i, j)].vis_players = vector<bool>(num_players_, false);
    }
  }

  for (int i = 0; i < num_players_; ++i) {
    Pos random_pos(rand() % board_size_, rand() % board_size_);
    if ((int)player_.size() <= i) {
      player_.push_back(random_pos);
    } else {
      player_[i].player.pos = random_pos;
      player_[i].player.score = 0;
    }
    board_[random_pos].vis_players[i] = true;
  }

  current_turn_ = 0;
  no_current_round_ = false;
  ++current_round_;
  LOG(INFO) << "Changed round to " << current_round_;
}

void ServerGame::Run() {
  current_round_ = 0;
  InitRound();
  std::chrono::system_clock::time_point new_round_at;
  while (current_round_ < NUM_ROUNDS) {
    if (no_current_round_) {
      // Check if new round should already start.
      if (std::chrono::system_clock::now() >= new_round_at) {
        InitRound();
      }
    } else {
      // Check if there is a time for a new turn.
      if (std::chrono::system_clock::now() >= TimeOfNewTurn()) {
        NewTurn();
      }
      if (current_turn_ > NUM_TURNS) {
        no_current_round_ = true;
        new_round_at =
            std::chrono::system_clock::now() +
            std::chrono::milliseconds(TIME_BETWEEN_ROUNDS_MILLISECONDS);
      }
    }
    std::mutex cv_mutex;
    std::unique_lock<std::mutex> lk(cv_mutex);
    // Start a thread that will run as soon as the condition_variable starts
    // waiting. This ensures that if new command is received, the
    // condition_variable really gets notified.
    std::thread thread_new_commands([this, &cv_mutex] {
      std::lock_guard<std::mutex> lk2(cv_mutex);
      // Process the commands that were already received. It is necessary here
      // because otherwise some command could be already received and
      // condition_variable wouldn't be notified.
      ProcessCommands();
      // Start waiting for new commands. Signal the condition_variable when
      // command from some player is ready.
      GetNewCommands();
    });
    auto wakeup_at = (no_current_round_ ? new_round_at : TimeOfNewTurn());
    cv_command_received_.wait_until(lk, wakeup_at);
    // Unlock the lock to avoid deadlock. It could occur if we didn't wait long
    // enough for thread_new_commands to acquire the lock.
    lk.unlock();
    thread_new_commands.join();
    // Process all the commands that were already received.
    ProcessCommands();
  }
}

void ServerGame::RunWithVisualizer() {
  window_ = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(
      sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Candy Eaters -- Server"));

  std::thread game([this] { this->Run(); });
  while (window_->isOpen()) {
    sf::Event event;
    while (window_->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_->close();
      }
    }
    Render();
    this_thread::sleep_for(chrono::milliseconds(10));
  }
  game.join();
}

void ServerGame::ListenForPlayers(const vector<int>& ports) {
  CHECK_EQ(num_players_, (int)ports.size());
  for (int i = 0; i < num_players_; ++i) {
    int port = ports[i];
    player_stream_.push_back(ServerStream([port] {
      return unique_ptr<StreamBackendInterface>(new StreamTcpServer(port));
    }));
    player_future_command_.push_back(std::future<void>());
    player_command_.push_back("");
  }
}

std::chrono::system_clock::time_point ServerGame::TimeOfNewTurn() {
  return last_turn_time_ + chrono::milliseconds(turn_length_milliseconds_);
}

void ServerGame::NewTurn() {
  // Do the moves that were received during the last turn.
  ProcessMoves();
  // With probability 1 - 1/(num_players_ + 1), add new candy.
  if (rand() % (num_players_ + 1) != 0) {
    Pos pos(rand() % board_size_, rand() % board_size_);
    ++board_[pos].num_candies;
  }
  ++current_turn_;
  LOG(INFO) << "Changed turn to " << current_turn_;
  last_turn_time_ = chrono::system_clock::now();
  SendOkToWaiting();
}

void ServerGame::ProcessMoves() {
  vector<int> order;
  for (int p = 0; p < num_players_; ++p) order.push_back(p);
  // Process the moves in random order.
  random_shuffle(order.begin(), order.end());
  for (int pi = 0; pi < num_players_; ++pi) {
    int p = order[pi];
    // If player moved in the current turn.
    if (player_[p].move.get_turn_id() == current_turn_) {
      if (player_[p].move.get_move_type() == ServerMove::MoveType::kEatCandy) {
        ProcessMoveEatCandy(p);
      }
      if (player_[p].move.get_move_type() == ServerMove::MoveType::kMove) {
        ProcessMoveMove(p);
      }
    }
  }
}

void ServerGame::ProcessMoveEatCandy(int pid) {
  CHECK_EQ(player_[pid].move.get_move_type(), ServerMove::MoveType::kEatCandy);
  if (board_[player_[pid].pos()].num_candies > 0) {
    --board_[player_[pid].pos()].num_candies;
    ++player_[pid].player.score;
  }
}
void ServerGame::ProcessMoveMove(int pid) {
  CHECK_EQ(player_[pid].move.get_move_type(), ServerMove::MoveType::kMove);
  board_[player_[pid].player.pos].vis_players[pid] = false;
  player_[pid].player.pos = player_[pid].move.get_move_to_pos();
  board_[player_[pid].player.pos].vis_players[pid] = true;
}

void ServerGame::SendOkToWaiting() {
  for (int p = 0; p < num_players_; ++p) {
    if (player_[p].waiting) {
      player_stream_[p].ReplyWithOk();
      player_[p].waiting = false;
    }
  }
}

void ServerGame::GetNewCommands() {
  for (int p = 0; p < num_players_; ++p) {
    if (player_stream_[p].Connected()) {
      if (player_[p].auth_state == kNone) {
        player_stream_[p].SendMessage("LOGIN");
        player_[p].auth_state = AuthState::kLoginSentToPlayer;
      }
      if (!player_future_command_[p].valid()) {
        player_future_command_[p] = player_stream_[p].GetFutureMessage(
            cv_command_received_, &player_command_[p]);
      }
    }
  }
}
void ServerGame::ProcessCommands() {
  for (int p = 0; p < num_players_; ++p) {
    if (player_stream_[p].Disconnected()) {
      LOG(WARNING) << "Player disconnected, connecting again";
      // If he was waiting, we don't want to send him OK when he connects again.
      player_[p].waiting = false;
      // Throw away any command coming from this player.
      player_future_command_[p] = std::future<void>();
      player_[p].auth_state = AuthState::kNone;
      player_stream_[p].ConnectAgain();
    }
    if (player_stream_[p].Connected()) {
      if (player_future_command_[p].valid() &&
          player_future_command_[p].wait_for(std::chrono::milliseconds(0)) ==
              std::future_status::ready) {
        player_future_command_[p].get();
        ProcessCommand(p, player_command_[p]);
      }
    }
  }
}

void ServerGame::ProcessCommand(int pid, const string& msg) {
  if (player_[pid].auth_state != AuthState::kAuthenticated) {
    if (player_[pid].auth_state == AuthState::kLoginSentToPlayer) {
      player_[pid].received_login = msg;
      player_stream_[pid].SendMessage("PASSWORD");
      player_[pid].auth_state = AuthState::kPasswordSentToPlayer;
      return;
    }
    if (player_[pid].auth_state == AuthState::kPasswordSentToPlayer) {
      player_[pid].received_password = msg;
      if (Authenticate(pid, player_[pid].received_login, player_[pid].received_password)) {
        player_stream_[pid].ReplyWithOk();
        player_[pid].auth_state = AuthState::kAuthenticated;
      } else {
        player_stream_[pid].ReplyWithError(kAuthError);
        player_[pid].auth_state = AuthState::kNone;
      }
      return;
    }
    return;
  }
  if (no_current_round_) {
    player_stream_[pid].ReplyWithError(kNoCurrentRound);
    return;
  }
  stringstream sstream(msg);
  string cmd;
  sstream >> cmd;
  if (cmd == "WAIT") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kWrongNumberOfArguments);
    } else {
      CmdWait(pid);
    }
  } else if (cmd == "GET_TIME") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kWrongNumberOfArguments);
    } else {
      CmdGetTime(pid);
    }
  } else if (cmd == "GET_MY_SCORE") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kWrongNumberOfArguments);
    } else {
      CmdGetMyScore(pid);
    }
  } else if (cmd == "GET_ALL_SCORES") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kWrongNumberOfArguments);
    } else {
      CmdGetAllScores(pid);
    }
  } else if (cmd == "GET_INIT") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kWrongNumberOfArguments);
    } else {
      CmdGetInit(pid);
    }
  } else if (cmd == "GET_MY_POS") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kWrongNumberOfArguments);
    } else {
      CmdGetMyPos(pid);
    }
  } else if (cmd == "GET_CANDY_COUNT") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kWrongNumberOfArguments);
    } else {
      CmdGetCandyCount(pid);
    }
  } else if (cmd == "EAT_CANDY") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kWrongNumberOfArguments);
    } else {
      CmdEatCandy(pid);
    }
  } else if (cmd == "MOVE") {
    int x, y;
    sstream >> x >> y;
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kWrongNumberOfArguments);
    } else {
      CmdMove(pid, Pos(x, y));
    }
  } else {
    player_stream_[pid].ReplyWithError(kInvalidCommand);
  }
}

void ServerGame::CmdWait(int pid) {
  player_stream_[pid].ReplyWithOk();
  player_stream_[pid].SendMessage("WAITING");
  player_[pid].waiting = true;
}
void ServerGame::CmdGetTime(int pid) {
  player_stream_[pid].ReplyWithOk();
  player_stream_[pid].SendMessage(to_string(current_round_) + " " + to_string(current_turn_) + " " + to_string(NUM_TURNS));
}
void ServerGame::CmdGetMyScore(int pid) {
  player_stream_[pid].ReplyWithOk();
  int score = player_[pid].player.score;
  player_stream_[pid].SendMessage(to_string(score));
}
void ServerGame::CmdGetAllScores(int pid) {
  vector<int> scores;
  for (auto p : player_) {
    scores.push_back(p.player.score);
  }
  sort(scores.begin(), scores.end());
  string scores_str;
  for (int i = 0; i < (int)scores.size(); ++i) {
    if (i) scores_str.push_back(' ');
    scores_str += to_string(scores[i]);
  }
  player_stream_[pid].ReplyWithOk();
  player_stream_[pid].SendMessage(to_string(player_.size()));
  player_stream_[pid].SendMessage(scores_str);
}
void ServerGame::CmdGetInit(int pid) {
  player_stream_[pid].ReplyWithOk();
  player_stream_[pid].SendMessage(to_string(board_size_));
}
void ServerGame::CmdGetMyPos(int pid) {
  player_stream_[pid].ReplyWithOk();
  Pos pos = player_[pid].pos();
  string pos_msg = to_string(pos.x()) + " " + to_string(pos.y());
  player_stream_[pid].SendMessage(pos_msg);
}
void ServerGame::CmdGetCandyCount(int pid) {
  player_stream_[pid].ReplyWithOk();
  player_stream_[pid].SendMessage(
      to_string(board_[player_[pid].pos()].num_candies));
}
void ServerGame::CmdEatCandy(int pid) {
  if (player_[pid].move.get_turn_id() == current_turn_) {
    player_stream_[pid].ReplyWithError(kErrorOneMove);
    return;
  }
  if (board_[player_[pid].pos()].num_candies <= 0) {
    player_stream_[pid].ReplyWithError(kNoCandies);
    return;
  }
  player_[pid].move = ServerMove::EatCandy(current_turn_);
  player_stream_[pid].ReplyWithOk();
}
void ServerGame::CmdMove(int pid, Pos pos) {
  if (player_[pid].move.get_turn_id() == current_turn_) {
    player_stream_[pid].ReplyWithError(kErrorOneMove);
    return;
  }
  if (!board_.inside(pos) || !player_[pid].NeighbourCell(pos)) {
    player_stream_[pid].ReplyWithError(kInvalidMove);
    return;
  }
  player_[pid].move = ServerMove::Move(current_turn_, pos);
  player_stream_[pid].ReplyWithOk();
}

void ServerGame::Render() {
  window_->clear(sf::Color::Black);
  Board<ServerCell> board_for_drawing = board_;
  double cell_size = static_cast<double>(WINDOW_SIZE) / board_size_;
  board_for_drawing.setScale(cell_size, cell_size);
  window_->draw(board_for_drawing);
  window_->display();
}
