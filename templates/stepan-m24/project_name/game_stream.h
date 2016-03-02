#ifndef GAME_STREAM_H_
#define GAME_STREAM_H_

#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "c24/c24.h"

#include "objects.h"
using namespace std;

using c24::communication::Status;
using c24::communication::Stream;
using c24::communication::StreamBackendInterface;

// Send commands to server and retrieve the data from response.
class GameStream {
 public:
  GameStream(std::unique_ptr<StreamBackendInterface> stream_backend);
  Status LastStatus() const { return stream_.LastStatus(); }
  bool Authenticate(const string& login, const string& password);
  // Send WAIT and block until messages "OK, WAITING, OK" are received (or
  // until one of the messages is not as expected).
  bool Wait();
  // Put here the commands you want to use.
  bool GetTime(int *round, int *turn, int *turns_in_round);
  bool GetMyScore(int *score);
  bool GetAllScores(vector<int>* all_scores);
  bool GetInit(int *n);
  bool Move(const Pos& pos);

 private:
  Stream stream_;
};

#endif  // GAME_STREAM_H_
