#ifndef GAME_H_
#define GAME_H_

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

#define LOGIN "login"
#define PASSWORD "password"

class Game {
 public:
  Game(const string& host, int port);
  void Run(bool visualizer, bool toolbar);

 private:
  // Run the actual logic of the program.
  void RunGame();
  // If there is a candy, eat it, otherwise move to some neihbour cell.
  void Move(bool plan_future = false);
  void GetCurrentState();
  // Check if there was manual move done with keyboard and if yes, do it.
  // Returns true if move from player was received.
  bool ManualMove(bool plan_future);
  void DoMoveEatCandy(bool plan_future);
  void DoMoveMove(Pos new_pos, bool plan_future);

  Pos ChooseWhereToMoveRandom();

  bool ValidMove(Pos from_pos, Pos to_pos);
  void ChangeFuturePos(Pos new_pos);

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
  Player player_;
  Pos manual_pos_;

  std::unique_ptr<sf::RenderWindow> window_;
  int board_size_;
  Board<Cell> board_;
  int current_round_, last_current_round_;
  int current_turn_;

  sfg::SFGUI sfgui_;
  ToolPrintVariables tool_print_variables_;
  std::unique_ptr<SfguiWindow> sfgui_window_;

  const int kErrorNoCurrentRound = 9;

  int port_;
};

#endif  // GAME_H_
