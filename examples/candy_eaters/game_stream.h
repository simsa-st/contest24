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
  // Send WAIT and block until messages "OK, WAITING, OK" are received (or
  // until one of the messages is not as expected).
  bool Authenticate(const string& login, const string& password);
  bool Wait();
  bool GetInit(int* n);
  bool GetMyPos(Pos* pos);
  bool GetMyScore(int* score);
  bool GetCandyCount(int* candy_count);
  bool EatCandy();
  bool Move(Pos pos);

 private:
  Stream stream_;
};

#endif  // GAME_STREAM_H_
