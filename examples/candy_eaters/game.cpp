#include "game.h"

#include <thread>
#include <SFML/Graphics.hpp>

#include "c24/communication/stream_backend_interface.h"
#include "c24/communication/stream_tcp_client.h"

std::string print_bool(bool x) {
  if (x) return "True";
  return "False";
}

using c24::communication::StreamBackendInterface;
using c24::communication::StreamTcpClient;

Game::Game(const string& host, int port)
    : game_stream_(GameStream(
          unique_ptr<StreamBackendInterface>(new StreamTcpClient(host, port)))) {
  board_size_ = game_stream_.GetInit();
  board_ = Board<Cell>(board_size_);
  player_.pos = game_stream_.GetMyPos();
  board_[player_.pos].vis_player = true;
  current_turn_ = 0;

  for (int d = 0; d < 4; ++d) go_to_dir_[d] = false;
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
  }
  // Close the second window if it is still open.
  if (visualizer && window_->isOpen()) window_->close();
  if (toolbar && sfgui_window_->isOpen()) sfgui_window_->close();

  // Wait for the game thread.
  game.join();
}

void Game::RunGame() {
  while (true) {
    Move();
    // Wait until next round.
    while (!game_stream_.Wait());
    ++current_turn_;
  }
}

void Game::InitVisualizer() {
  window_ = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(
      sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "My window"));
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
  tool_print_variables_.AddVariableCustomPrint("left", &go_to_dir_[0],
                                               &print_bool, 0.01);
  tool_print_variables_.AddVariableCustomPrint("down", &go_to_dir_[1],
                                               &print_bool, 0.01);
  tool_print_variables_.AddVariableCustomPrint("right", &go_to_dir_[2],
                                               &print_bool, 0.01);
  tool_print_variables_.AddVariableCustomPrint("up", &go_to_dir_[3],
                                               &print_bool, 0.01);
  sfgui_window_->AddWindow(tool_print_variables_.WindowPtr());
}

void Game::Move() {
  GetCurrentState();
  if (ManualMove()) return;

  if (board_[player_.pos].last_seen_candies > 0) {
    DoMoveEatCandy();
  } else {
    DoMoveMove(ChooseWhereToMoveRandom());
  }
}

void Game::GetCurrentState() {
  player_.score = game_stream_.GetMyScore();
  player_.pos = game_stream_.GetMyPos();
  board_[player_.pos].last_turn_visited = current_turn_;
  board_[player_.pos].last_seen_candies = game_stream_.GetCandyCount();
  board_[player_.pos].just_eating = false;
}

bool Game::ManualMove() {
  for (int d = 0; d < 4; ++d) {
    if (go_to_dir_[d]) {
      go_to_dir_[d] = false;
      Pos new_pos = player_.pos.move(d);
      if (board_.inside(new_pos)) {
        DoMoveMove(new_pos);
        return true;
      }
    }
  }
  return false;
}

void Game::DoMoveEatCandy() {
  game_stream_.EatCandy();
  board_[player_.pos].just_eating = true;
}

void Game::DoMoveMove(Pos new_pos) {
  game_stream_.Move(new_pos);
  board_[player_.pos].vis_player = false;
  player_.pos = new_pos;
  board_[player_.pos].vis_player = true;
}

Pos Game::ChooseWhereToMoveRandom() {
  Pos new_pos(-1, -1);
  while (!board_.inside(new_pos)) {
    int random_dir = rand() % 4;
    new_pos = player_.pos.move(random_dir);
  }
  return new_pos;
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
      for (int i = 0; i < 4; ++i) go_to_dir_[i] = false;
      if (event.key.code == sf::Keyboard::Left) {
        go_to_dir_[0] = true;
      }
      if (event.key.code == sf::Keyboard::Down) {
        go_to_dir_[1] = true;
      }
      if (event.key.code == sf::Keyboard::Right) {
        go_to_dir_[2] = true;
      }
      if (event.key.code == sf::Keyboard::Up) {
        go_to_dir_[3] = true;
      }
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
