#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <memory>

#include "SFGUI/SFGUI.hpp"

#include "c24/c24.h"
#include "game_stream.h"
#include "objects.h"
#include "toolbar_functions.h"

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
  const int kErrorNoCurrentRound = 9;

  // Run the actual logic of the program.
  void RunGame();
  void Move();
  void WaitForNewTurn();
  void NewRound();
  void NewTurn();
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

  // Game state variables.
  int port_;
  int current_round_, current_turn_, num_of_turns_in_round_;
  int board_size_;
  Player player_;
  Board<Cell> board_;

  // Toolbar variables.
  vector<int> all_scores_;
  pair<int, pair<int, int> > turn_time_;
};

#endif  // GAME_H_
