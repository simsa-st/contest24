#ifndef OBJECTS_PLAYER_H_
#define OBJECTS_PLAYER_H_

#include <string>

#include "pos.h"

struct Player {
  Player() {}
  Player(const Pos& _pos) : pos(_pos) {}

  std::string Print() const;

  Pos pos, future_pos;
  int score;
};

std::string print_player(Player p);

#endif  // OBJECTS_PLAYER_H_
