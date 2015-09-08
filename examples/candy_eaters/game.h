#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <memory>

#include "c24/communication/stream.h"

#include "game_stream.h"
using namespace std;

class Game {
 public:
  Game(const string& host, int port);
  void Run();

  // TODO(simsa-st): Comming soon.
  void RunWithVisualizer();
  // void RunWithoutLoop();
 private:
  // If there is a candy, eat it, otherwise move to some neihbour cell.
  void Move();

  // GameStream is for sending the commands to server.
  GameStream game_stream_;
  Player player_;

  // TODO(simsa-st): Comming soon.
  // void Render();
  // Visualizer vis_;
};

#endif  // GAME_H_
