#include "game.h"

#include "c24/communication/stream_backend_interface.h"
#include "c24/communication/stream_tcp_client.h"

using c24::communication::StreamBackendInterface;
using c24::communication::StreamTcpClient;

Game::Game(const string& host, int port)
    : game_stream_(GameStream(unique_ptr<StreamBackendInterface>(
          new StreamTcpClient(host, port)))) {}

void Game::Run() {
  while (true) {
    // ProcessEvents();
    Move();

    // Wait until next round.
    while (!game_stream_.Wait());
  }
}

void Game::RunWithVisualizer() {
  // init visualizer;
  // open window with some layout
  // while (window.open()) {
  //   handle events
  //   handle commands
  //   std::thread program_loop([]() { while (loop()); });
  // }
  // while (program_loop alive) {
  //   handle commands
  // }
  // program_loop.join();
}

void Game::Move() {
  // We don't really use the score but it is handy when checking the logs.
  game_stream_.GetMyScore();
  int candy_count = game_stream_.GetCandyCount();
  if (candy_count) {
    game_stream_.EatCandy();
  } else {
    Pos pos = game_stream_.GetMyPos();
    int random_dir = rand() % 4;
    Pos new_pos = pos.move(random_dir);
    game_stream_.Move(new_pos);
  }
}
