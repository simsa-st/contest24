#ifndef OBJECTS_PLAYER_H_
#define OBJECTS_PLAYER_H_

#include "pos.h"

struct Player {
  Player() {}
  Player(const Pos& _pos) : pos(_pos) {}

  Pos pos;
  int score;
};

#endif  // OBJECTS_PLAYER_H_
