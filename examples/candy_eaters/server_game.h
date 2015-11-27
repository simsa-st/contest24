#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include "c24/c24.h"

#include "server_objects.h"
using namespace std;

#define BOARD_SIZE 5
#define TURN_LENGTH_MICROS 1000000
#define NUM_TURNS 5000
#define WINDOW_SIZE 400

// Server for Candy Eaters game. Communicates with all the players, replies to
// their queries and manages the state of the game.
class ServerGame {
 public:
  ServerGame(vector<int> ports)
      : ServerGame(ports, BOARD_SIZE, TURN_LENGTH_MICROS) {}
  ServerGame(vector<int> ports, int board_size, int turn_length_micros);
  void Run();
  void RunWithVisualizer();
 private:
  // Start listening for tcp connections at given ports.
  void ListenForPlayers(const vector<int>& ports);

  // Check the clock if there is a time for a new turn.
  bool TimeForNewTurn();
  // Start a new turn.
  void NewTurn();
  // Process moves players did in the last turn in random order.
  void ProcessMoves();
  // Process move EAT_CANDY
  void ProcessMoveEatCandy(int pid);
  // Process move MOVE
  void ProcessMoveMove(int pid);
  // Send OK to all players that sent WAIT in the previous turn.
  void SendOkToWaiting();

  // Manage the connections to players and process all the received commands.
  void ProcessCommands();
  // Process one command given by a player with id pid.
  void ProcessCommand(int pid, string msg);
  // Individual commands.
  void CmdWait(int pid);
  void CmdGetInit(int pid);
  void CmdGetMyPos(int pid);
  void CmdGetMyScore(int pid);
  void CmdGetCandyCount(int pid);
  void CmdEatCandy(int pid);
  void CmdMove(int pid, Pos pos);

  // Error messages.
  const string kErrorOneMove = "YOU CAN DO ONLY ONE MOVE PER TURN";
  const string kInvalidMove = "INVALID MOVE";
  const string kInvalidCommand = "INVALID COMMAND";
  const string kTooManyArguments = "TOO MANY ARGUMENTS";
  const string kNoCandies = "NO CANDY ON THIS POSITION";

  int board_size_;
  // How long players have for one turn.
  int turn_length_micros_;

  chrono::system_clock::time_point last_turn_time_;
  // Number of current turn.
  int current_turn_;
  int num_players_;
  vector<c24::communication::ServerStream> player_stream_;
  vector<ServerPlayer> player_;
  Board<ServerCell> board_;
};

#endif  // SERVER_GAME_H_
