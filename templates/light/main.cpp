#include <memory>
#include <string>
#include <thread>

#include "c24/c24.h"
#include <glog/logging.h>
#include <gflags/gflags.h>
#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using c24::communication::Status;
using c24::communication::Stream;
using c24::communication::StreamBackendInterface;
using c24::communication::StreamTcpClient;
using c24::toolbar::SfguiWindow;
using c24::toolbar::ToolPrintVariables;

#define WINDOW_SIZE 400
#define TOOLBAR_WINDOW_SIZE 200

DEFINE_string(host, "127.0.0.1", "Host for tcp communication.");
DEFINE_int32(port, 5500, "Port for tcp communication.");
DEFINE_bool(vis, false, "Start with visualizer.");
DEFINE_bool(toolbar, false, "Start with toolbar.");
DEFINE_int32(seed, -1,
             "Seed used in srand. If negative (default), time(NULL) is used.");

// Send commands to server and retrieve the data from response.
class GameStream {
 public:
  GameStream(std::unique_ptr<StreamBackendInterface> stream_backend)
      : stream_(std::move(stream_backend)) {}
  Status LastStatus() const { return stream_.LastStatus(); }
  // Send WAIT and block until messages "OK, WAITING, OK" are received (or
  // until one of the messages is not as expected).
  bool Wait() {
    // Send WAIT and check that the server responds with OK, WAITING and OK.
    if (!stream_.SendMessageWithCheck("WAIT", "OK")) return false;
    if (!stream_.GetMessageWithCheck("WAITING")) return false;
    return stream_.GetMessageWithCheck("OK");
  }
  // Put here the commands you want to use.
  // bool GetInit(int* n) {
  //   if (!stream_.SendMessageWithCheck("GET_INIT")) return false;
  //   *n = stream_.GetVectorOf<int>(1)[0];
  //   return LastStatus().Ok();
  // }
  // bool Move(int x, int y) {
  //   return stream_.SendMessageWithCheck("MOVE " + to_string(x) + " " +
  //                                       to_string(y));
  // }

 private:
  Stream stream_;
};

class Game {
 public:
  Game(const string& host, int port);
  void Run(bool visualizer, bool toolbar);

 private:
  // TODO: Initialize this with the correct value.
  const int kErrorNoCurrentRound = -1;

  // Run the actual logic of the program.
  void RunGame();
  void Move();
  void WaitForNewTurn();
  void NewRound();
  // Init visualizer window.
  void InitVisualizer();
  // Init toolbar window.
  void InitToolbar();
  void ProcessEvents();
  void Render();

  // GameStream is for sending the commands to server.
  GameStream game_stream_;
  std::unique_ptr<sf::RenderWindow> window_;
  sfg::SFGUI sfgui_;
  ToolPrintVariables tool_print_variables_;
  std::unique_ptr<SfguiWindow> sfgui_window_;
  int current_round_, last_current_round_, current_turn_;
  int port_;
};

Game::Game(const string& host, int port)
    : game_stream_(GameStream(
          unique_ptr<StreamBackendInterface>(new StreamTcpClient(host, port)))),
      port_(port) {
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
  // game_stream_.GetMyPos(&pos);
  // game_stream_.Move(pos.x + 1, pos.y);
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
  // TODO: Put here and inside of the loop the first command that you want to
  // send to the server when new round starts.

  // game_stream_.GetInit(&board_size_);
  while (game_stream_.LastStatus().error_code == kErrorNoCurrentRound) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    // game_stream_.GetInit(&board_size_);
  }
  // Reinitialize the variables.
  current_turn_ = 0;
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

  tool_print_variables_.AddVariable("current_turn", &current_turn_, 0.01);
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
  // double cell_size = static_cast<double>(WINDOW_SIZE) / board.size();
  // board.setScale(cell_size, cell_size);
  // window_->draw(board);
  window_->display();
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(*argv);
  google::ParseCommandLineFlags(&argc, &argv, true);

  int seed = FLAGS_seed;
  if (seed < 0) seed = time(NULL);
  srand(seed);

  Game game(FLAGS_host, FLAGS_port);
  game.Run(FLAGS_vis, FLAGS_toolbar);
  return 0;
}
