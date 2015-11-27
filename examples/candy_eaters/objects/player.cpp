#include "player.h"

std::string Player::Print() const {
  return "player<pos: " + pos.Print() + ", score: " + std::to_string(score) + ">";
}

std::string print_player(Player p) {
  return p.Print();
}
