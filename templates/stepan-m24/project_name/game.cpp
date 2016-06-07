#include "game.h"

#include <chrono>
#include <thread>

#include "easylogging.h"
#include <SFML/Graphics.hpp>

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
    WaitForNewTurn();
  }
}
void Game::Move() {
  Pos pos;
  // game_stream_.GetMyPos(&pos);
  game_stream_.Move(pos.Move(Direction::FromChar('R')));
}
void Game::WaitForNewTurn() {
  while (!game_stream_.Wait()) {
    if (game_stream_.LastStatus().error_code == kErrorNoCurrentRound) {
      ++current_round_;
      NewRound();
      return;
    }
  }
  int round;
  game_stream_.GetTime(&round, &current_turn_, &num_of_turns_in_round_);
  if (current_round_ != round) {
    current_round_ = round;
    NewRound();
    return;
  } else {
    NewTurn();
  }
}
void Game::NewRound() {
  game_stream_.GetInit(&board_size_);
  while (game_stream_.LastStatus().error_code == kErrorNoCurrentRound) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    game_stream_.GetInit(&board_size_);
  }
  // Reinitialize the variables.
  board_ = Board<Cell>(board_size_);
  current_turn_ = 0;
}
void Game::NewTurn() {
  turn_time_.first = current_round_;
  turn_time_.second.first = current_turn_;
  turn_time_.second.second = num_of_turns_in_round_;
  game_stream_.GetMyScore(&player_.score);
  game_stream_.GetAllScores(&all_scores_);
  for (int i = 0; i < (int)all_scores_.size(); ++i) {
    if (all_scores_[i] == player_.score) {
      player_.rank.second = i + 1;
      if (i == 0 || all_scores_[i] != all_scores_[i - 1]) {
        player_.rank.first = i + 1;
      }
    }
  }
}
void Game::InitVisualizer() {
  window_ = std::unique_ptr<sf::RenderWindow>(
      new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE),
                           "Game -- Player, port " + to_string(port_)));
  window_->setVerticalSyncEnabled(true);
}
void Game::InitToolbar() {
  sfgui_window_ = std::unique_ptr<SfguiWindow>(
      new SfguiWindow(&sfgui_, TOOLBAR_WINDOW_SIZE, TOOLBAR_WINDOW_SIZE));
  tool_print_variables_.AddVariableCustomPrint("time", &turn_time_, &print_time, 0.02);
  tool_print_variables_.AddVariableCustomPrint("player", &player_, &print_player, 0.05);
  tool_print_variables_.AddVariableCustomPrint("all_scores", &all_scores_, &print_all_scores, 0.1);
  sfgui_window_->AddWindow(tool_print_variables_.WindowPtr());
}
void Game::ProcessEvents() {
  sf::Event event;
  while (window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_->close();
    }
  }
}
void Game::Render() {
  window_->clear(sf::Color::Black);
  double cell_size = static_cast<double>(WINDOW_SIZE) / board_size_;
  board_.setScale(cell_size, cell_size);
  window_->draw(board_);
  window_->display();
}
