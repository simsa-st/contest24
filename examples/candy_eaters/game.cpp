#include "game.h"

#include <thread>
#include <SFML/Graphics.hpp>

std::string print_bool(bool x) {
  if (x) return "True";
  return "False";
}

using c24::communication::StreamBackendInterface;
using c24::communication::StreamTcpClient;

Game::Game(const string& host, int port)
    : game_stream_(GameStream(
          unique_ptr<StreamBackendInterface>(new StreamTcpClient(host, port)))),
      port_(port) {
  if (!game_stream_.Authenticate(LOGIN, PASSWORD)) {
    LOG(FATAL) << "Authentication failed";
  }
  NewRound();
}

void Game::Run(bool visualizer, bool toolbar) {
  if (!visualizer && !toolbar) {
    RunGame();
    return;
  }
  if (visualizer) InitVisualizer();
  if (toolbar) InitToolbar();
  std::thread game([this] { this->RunGame(); });

  // Keep the windows alive while all of the windows that were initially open
  // are still open.
  while ((!visualizer || window_->isOpen()) &&
         (!toolbar || sfgui_window_->isOpen())) {
    if (visualizer) {
      ProcessEvents();
      Render();
    }
    if (toolbar) {
      sfgui_window_->ProcessEvents();
      sfgui_window_->Render();
    }
    this_thread::sleep_for(chrono::milliseconds(10));
  }
  // Close the second window if it is still open.
  if (visualizer && window_->isOpen()) window_->close();
  if (toolbar && sfgui_window_->isOpen()) sfgui_window_->close();

  // Wait for the game thread.
  game.join();
}

void Game::RunGame() {
  current_round_ = 0;
  while (true) {
    Move();
    manual_pos_ = Pos(-1, -1);
    Move(true);
    WaitForNewTurn();
  }
}

void Game::InitVisualizer() {
  window_ = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(
      sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE),
      "Candy Eaters -- Player, port " + to_string(port_)));
  window_->setVerticalSyncEnabled(true);
}
void Game::InitToolbar() {
  sfgui_window_ = std::unique_ptr<SfguiWindow>(
      new SfguiWindow(&sfgui_, TOOLBAR_WINDOW_SIZE, TOOLBAR_WINDOW_SIZE));

  tool_print_variables_.AddVariable("board_size", &board_size_, 0.01);
  tool_print_variables_.AddVariable("current_turn", &current_turn_, 0.01);
  tool_print_variables_.AddVariable("candies", &(player_.score), 0.01);
  tool_print_variables_.AddVariableCustomPrint("player", &player_,
                                               &print_player, 0.1);
  sfgui_window_->AddWindow(tool_print_variables_.WindowPtr());
}

void Game::Move(bool plan_future) {
  if (!plan_future) {
    GetCurrentState();
  }
  if (ManualMove(plan_future)) return;

  if (board_[player_.pos].last_seen_candies > 0) {
    DoMoveEatCandy(plan_future);
  } else {
    Pos new_pos;
    if (!plan_future && ValidMove(player_.pos, player_.future_pos)) {
      new_pos = player_.future_pos;
    } else {
      new_pos = ChooseWhereToMoveRandom();
    }
    DoMoveMove(new_pos, plan_future);
  }
}

void Game::GetCurrentState() {
  game_stream_.GetMyScore(&player_.score);
  game_stream_.GetMyPos(&player_.pos);
  board_[player_.pos].last_turn_visited = current_turn_;
  game_stream_.GetCandyCount(&board_[player_.pos].last_seen_candies);
}

bool Game::ManualMove(bool plan_future) {
  if (ValidMove(player_.pos, manual_pos_)) {
    DoMoveMove(manual_pos_, plan_future);
    return true;
  }
  return false;
}

void Game::DoMoveEatCandy(bool plan_future) {
  if (plan_future) {
    board_[player_.pos].just_eating = true;
    ChangeFuturePos(Pos(-1, -1));
  } else {
    game_stream_.EatCandy();
    --board_[player_.pos].last_seen_candies;
  }
}

void Game::DoMoveMove(Pos new_pos, bool plan_future) {
  board_[player_.pos].just_eating = false;
  if (plan_future) {
    ChangeFuturePos(new_pos);
  } else {
    game_stream_.Move(new_pos);
    board_[player_.pos].vis_player = false;
    player_.pos = new_pos;
    board_[player_.pos].vis_player = true;
    ChangeFuturePos(Pos(-1, -1));
  }
}

Pos Game::ChooseWhereToMoveRandom() {
  Pos new_pos(-1, -1);
  while (!board_.inside(new_pos)) {
    int random_dir = rand() % 4;
    new_pos = player_.pos.move(random_dir);
  }
  return new_pos;
}

bool Game::ValidMove(Pos from_pos, Pos to_pos) {
  if (!board_.inside(to_pos)) return false;
 for (int dir = 0; dir < 4; ++dir) {
   if (from_pos.move(dir) == to_pos) return true;
 }
 return false;
}
void Game::ChangeFuturePos(Pos new_pos) {
  if (board_.inside(player_.future_pos)) {
    board_[player_.future_pos].vis_future_player = false;
  }
  player_.future_pos = new_pos;
  if (ValidMove(player_.pos, player_.future_pos)) {
    board_[player_.future_pos].vis_future_player = true;
  }
}

void Game::WaitForNewTurn() {
  while (!game_stream_.Wait()) {
    if (game_stream_.LastStatus().error_code == kErrorNoCurrentRound) {
      ++current_round_;
      break;
    }
  }
  if (current_round_ != last_current_round_) {
    NewRound();
    last_current_round_ = current_round_;
  }
  ++current_turn_;
}
void Game::NewRound() {
  player_.score = 0;
  game_stream_.GetInit(&board_size_);
  while (game_stream_.LastStatus().error_code == kErrorNoCurrentRound) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    game_stream_.GetInit(&board_size_);
  }
  board_ = Board<Cell>(board_size_);
  game_stream_.GetMyPos(&player_.pos);
  manual_pos_ = Pos(-1, -1);
  board_[player_.pos].vis_player = true;
  current_turn_ = 0;
}

void Game::ProcessEvents() {
  sf::Event event;
  while (window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_->close();
    }
    if (event.type == sf::Event::KeyPressed) {
      // Cancel previous requests for move, even when something else than arrow
      // is pressed.
      manual_pos_ = Pos(-1, -1);
      int dir = -1;
      if (event.key.code == sf::Keyboard::Left) {
        dir = 0;
      }
      if (event.key.code == sf::Keyboard::Down) {
        dir = 1;
      }
      if (event.key.code == sf::Keyboard::Right) {
        dir = 2;
      }
      if (event.key.code == sf::Keyboard::Up) {
        dir = 3;
      }
      if (dir >= 0 && dir < 4) {
        manual_pos_ = player_.pos.move(dir);
      }
      Move(true);
    }
  }
}
void Game::Render() {
  window_->clear(sf::Color::Black);
  Board<Cell> board_for_drawing = board_;
  double cell_size = static_cast<double>(WINDOW_SIZE) / board_size_;
  board_for_drawing.setScale(cell_size, cell_size);
  for (auto pos : board_for_drawing) {
    board_[pos].now_turn = current_turn_;
  }
  window_->draw(board_for_drawing);
  window_->display();
}
