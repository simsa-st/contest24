#ifndef OBJECTS_SERVER_PLAYER_H_
#define OBJECTS_SERVER_PLAYER_H_

#include "player.h"
#include "pos.h"
#include "server_move.h"

#include <string>

enum AuthState { kNone = 0, kLoginSentToPlayer, kPasswordSentToPlayer, kAuthenticated };

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
  AuthState auth_state = kNone;
  std::string received_login, received_password;
};

#endif  // OBJECTS_SERVER_PLAYER_H_
