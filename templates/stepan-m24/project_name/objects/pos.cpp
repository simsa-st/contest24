#include "pos.h"

Pos Pos::Move(Direction dir) const {
  return Pos(x_ + dir.Shift()[0], y_ + dir.Shift()[1]);
}

std::string Pos::Print() const {
  return "pos<" + std::to_string(x_) + "," + std::to_string(y_) + ">";
}
