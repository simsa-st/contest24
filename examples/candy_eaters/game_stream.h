#ifndef GAME_STREAM_H_
#define GAME_STREAM_H_

#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "c24/c24.h"

#include "objects.h"
using namespace std;

using c24::communication::Stream;
using c24::communication::StreamBackendInterface;

// Send commands to server and retrieve the data from response.
class GameStream {
 public:
  GameStream(std::unique_ptr<StreamBackendInterface> stream_backend);
  // Send WAIT and block until message is not received. Return if it was OK.
  bool Wait();
  int GetInit();
  Pos GetMyPos();
  int GetMyScore();
  int GetCandyCount();
  void EatCandy();
  void Move(Pos pos);

 private:
  Stream stream_;
};

#endif  // GAME_STREAM_H_
