#ifndef OBJECTS_SERVER_PLAYER_H_
#define OBJECTS_SERVER_PLAYER_H_

#include "player.h"
#include "pos.h"
#include "server_move.h"

struct ServerPlayer {
  ServerPlayer(Pos pos) {
    player.pos = pos;
    player.score = 0;
  }
  Pos pos() const { return player.pos; }
  bool NeighbourCell(Pos pos) {
    int dx = pos.x() - player.pos.x();
    int dy = pos.y() - player.pos.y();
    return dx * dx + dy * dy == 1;
  }

  Player player;
  ServerMove move;
  bool waiting = false;
};

#endif  // OBJECTS_SERVER_PLAYER_H_
