#include "server_game.h"

#include <sstream>

#include <glog/logging.h>
#include "c24/communication/stream_backend_interface.h"
#include "c24/communication/stream_tcp_server.h"
#include "c24/communication/stream.h"

using c24::communication::StreamBackendInterface;
using c24::communication::StreamTcpServer;
using c24::communication::ServerStream;
using namespace std;

ServerGame::ServerGame(vector<int> ports, int board_size,
                       int turn_length_micros)
    : board_size_(board_size),
      turn_length_micros_(turn_length_micros),
      board_(board_size) {
  num_players_ = ports.size();

  for (int i = 0; i < board_size; ++i) {
    for (int j = 0; j < board_size; ++j) {
      board_[Pos(i, j)].num_candies = rand() % 5;
      board_[Pos(i, j)].vis_players = vector<bool>(num_players_, false);
    }
  }

  for (int i = 0; i < num_players_; ++i) {
    Pos random_pos(rand() % board_size_, rand() % board_size_);
    player_.push_back(random_pos);
    board_[random_pos].vis_players[i] = true;
  }

  ListenForPlayers(ports);
}

void ServerGame::Run() {
  while (current_turn_ < NUM_TURNS) {
    if (TimeForNewTurn()) {
      NewTurn();
    }
    ProcessCommands();
  }
}

void ServerGame::RunWithVisualizer() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "My window");

  std::thread game([this] { this->Run(); });
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::Black);
    Board<ServerCell> board_for_drawing = board_;
    double cell_size = static_cast<double>(WINDOW_SIZE) / board_size_;
    board_for_drawing.setScale(cell_size, cell_size);
    window.draw(board_for_drawing);
    window.display();
  }
  // while (program_loop alive) {
  //   handle commands
  // }
  game.join();
}

void ServerGame::ListenForPlayers(const vector<int>& ports) {
  CHECK_EQ(num_players_, (int)ports.size());
  for (int i = 0; i < num_players_; ++i) {
    int port = ports[i];
    player_stream_.push_back(ServerStream([port] {
      return unique_ptr<StreamBackendInterface>(new StreamTcpServer(port));
    }));
  }
}

bool ServerGame::TimeForNewTurn() {
  chrono::system_clock::time_point now = chrono::system_clock::now();
  return now - last_turn_time_ >= chrono::microseconds(turn_length_micros_);
}

void ServerGame::NewTurn() {
    ProcessMoves();
    ++current_turn_;
    LOG(INFO) << "Changed turn to " << current_turn_;
    if (rand() % (num_players_ + 1) != 0) {
      Pos pos(rand() % board_size_, rand() % board_size_);
      ++board_[pos].num_candies;
    }
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

void ServerGame::ProcessCommands() {
  for (int p = 0; p < num_players_; ++p) {
    if (player_stream_[p].Disconnected()) {
      LOG(WARNING) << "Player disconnected, connecting again";
      // If he was waiting, we don't want to send him OK when he connects again.
      player_[p].waiting = false;
      player_stream_[p].ConnectAgain();
    }
    if (player_stream_[p].Connected()) {
      if (player_stream_[p].MessageAvailable()) {
        string msg = player_stream_[p].GetMessage();
        ProcessCommand(p, msg);
      }
    }
  }
}

void ServerGame::ProcessCommand(int pid, string msg) {
  stringstream sstream(msg);
  string cmd;
  sstream >> cmd;
  if (cmd == "WAIT") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kTooManyArguments);
    } else {
      CmdWait(pid);
    }
  } else if (cmd == "GET_INIT") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kTooManyArguments);
    } else {
      CmdGetInit(pid);
    }
  } else if (cmd == "GET_MY_POS") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kTooManyArguments);
    } else {
      CmdGetMyPos(pid);
    }
  } else if (cmd == "GET_MY_SCORE") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kTooManyArguments);
    } else {
      CmdGetMyScore(pid);
    }
  } else if (cmd == "GET_CANDY_COUNT") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kTooManyArguments);
    } else {
      CmdGetCandyCount(pid);
    }
  } else if (cmd == "EAT_CANDY") {
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kTooManyArguments);
    } else {
      CmdEatCandy(pid);
    }
  } else if (cmd == "MOVE") {
    int x, y;
    sstream >> x >> y;
    if (sstream.rdbuf()->in_avail() != 0) {
      player_stream_[pid].ReplyWithError(kTooManyArguments);
    } else {
      CmdMove(pid, Pos(x, y));
    }
  } else {
    player_stream_[pid].ReplyWithError(kInvalidCommand);
  }
}

void ServerGame::CmdWait(int pid) {
  player_[pid].waiting = true;
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
void ServerGame::CmdGetMyScore(int pid) {
  player_stream_[pid].ReplyWithOk();
  int score = player_[pid].player.score;
  player_stream_[pid].SendMessage(to_string(score));
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
