#include "player.h"

std::string Player::Print() const {
  std::string str = "player<pos: " + pos.Print() + ", score: " +
                    std::to_string(score) + ", rank: " +
                    std::to_string(rank.first) + ".";
  if (rank.first != rank.second) {
    str += "-" + std::to_string(rank.second) + ".";
  }
  str.push_back('>');
  return str;
}

std::string print_player(Player p) {
  return p.Print();
}
