#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include <condition_variable>
#include <chrono>
#include <future>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "c24/c24.h"

#include "server_objects.h"
using namespace std;

#define MIN_BOARD_SIZE 5
#define MAX_BOARD_SIZE 10
#define NUM_TURNS 30
#define NUM_ROUNDS 1000
#define TURN_LENGTH_MILLISECONDS 1000
#define TIME_BETWEEN_ROUNDS_MILLISECONDS 3000
#define SLEEP_BETWEEN_COMMANDS_MILLIS 100

#define WINDOW_SIZE 400


// Server for Candy Eaters game. Communicates with all the players, replies to
// their queries and manages the state of the game.
class ServerGame {
 public:
  ServerGame(vector<int> ports);
  void Run();
  void RunWithVisualizer();
 private:
  // Prepare the board and positions of all players before the start of new
  // round.
  void InitRound();
  // Start listening for tcp connections at given ports.
  void ListenForPlayers(const vector<int>& ports);

  // Check the clock if there is a time for a new turn.
  std::chrono::system_clock::time_point TimeOfNewTurn();
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

  // Ensure that we are waiting for commands from every connected player.
  void GetNewCommands();
  // Process the commands that were already received. Start listening again for
  // the players that got disconnected.
  void ProcessCommands();
  // Process one command given by a player with id pid.
  void ProcessCommand(int pid, const string& msg);
  // Individual commands.
  void CmdWait(int pid);
  void CmdGetInit(int pid);
  void CmdGetMyPos(int pid);
  void CmdGetMyScore(int pid);
  void CmdGetCandyCount(int pid);
  void CmdEatCandy(int pid);
  void CmdMove(int pid, Pos pos);

  // Draw the board to the window.
  void Render();

  // Error messages.
  const pair<int, string> kWrongNumberOfArguments = {4, "Wrong number of arguments."};
  const pair<int, string> kNoCurrentRound = {9, "No current round."};
  const pair<int, string> kErrorOneMove = {101, "You can do only one move per turn."};
  const pair<int, string> kInvalidMove = {102, "Invalid move."};
  const pair<int, string> kInvalidCommand = {103, "Invalid command."};
  const pair<int, string> kNoCandies = {104, "No candy on this position."};

  int num_players_;
  int turn_length_milliseconds_;

  int board_size_;
  // Game state.
  vector<ServerPlayer> player_;
  Board<ServerCell> board_;

  chrono::system_clock::time_point last_turn_time_;
  bool no_current_round_;
  // Number of the current round and turn.
  int current_round_;
  int current_turn_;
  // Stream for every player.
  vector<c24::communication::ServerStream> player_stream_;
  // Condition variable that gets notified whenever command from some player is
  // received.
  std::condition_variable cv_command_received_;
  // Future to decide whether we are currently trying to receive a command from
  // a player and if we have already received it.
  std::vector<std::future<void>> player_future_command_;
  // The actual command received from the player.
  std::vector<std::string> player_command_;

  std::unique_ptr<sf::RenderWindow> window_;
};

#endif  // SERVER_GAME_H_
