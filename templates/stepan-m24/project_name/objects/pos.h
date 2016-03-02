#ifndef OBJECTS_POS_H_
#define OBJECTS_POS_H_

#include "direction.h"

#include <string>

class Pos {
 public:
  Pos() : Pos(0, 0) {}
  Pos(int x, int y) : x_(x), y_(y) {}
  int x() const { return x_; }
  int y() const { return y_; }
  Pos Move(Direction dir) const;

  std::string Print() const;

  bool operator==(const Pos& other) const {
    return x_ == other.x_ && y_ == other.y_;
  }
  bool operator!=(const Pos& other) const { return !(*this == other); }

 protected:
  int x_;
  int y_;
};

#endif  // OBJECTS_POS_H_
