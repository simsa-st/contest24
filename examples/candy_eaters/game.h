#ifndef GAME_H_
#define GAME_H_

#include <atomic>
#include <string>
#include <memory>

#include <SFGUI/SFGUI.hpp>

#include "c24/c24.h"
#include "game_stream.h"

using namespace std;
using c24::toolbar::SfguiWindow;
using c24::toolbar::ToolPrintVariables;

#define WINDOW_SIZE 400
#define TOOLBAR_WINDOW_SIZE 400

class Game {
 public:
  Game(const string& host, int port);
  void Run(bool visualizer, bool toolbar);

 private:
  // Run the actual logic of the program.
  void RunGame();

  // Init visualizer window.
  void InitVisualizer();

  // Init toolbar window.
  void InitToolbar();

  // If there is a candy, eat it, otherwise move to some neihbour cell.
  void Move();
  void GetCurrentState();

  // Check if there was manual move done with keyboard and if yes, do it.
  // Returns true if move from player was received.
  bool ManualMove();

  void DoMoveEatCandy();
  void DoMoveMove(Pos new_pos);

  Pos ChooseWhereToMoveRandom();

  void ProcessEvents();
  void Render();

  // GameStream is for sending the commands to server.
  GameStream game_stream_;
  Player player_;

  std::unique_ptr<sf::RenderWindow> window_;
  int board_size_;
  Board<Cell> board_;
  int current_turn_;

  bool go_to_dir_[4];

  sfg::SFGUI sfgui_;
  ToolPrintVariables tool_print_variables_;
  std::unique_ptr<SfguiWindow> sfgui_window_;

  // TODO(simsa-st): Comming soon.
  // void Render();
  // Visualizer vis_;
};

#endif  // GAME_H_
