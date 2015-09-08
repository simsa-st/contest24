#ifndef OBJECTS_POS_H_
#define OBJECTS_POS_H_

// TODO(simsa-st): Do a class from this, that is itterable (for (dir : dirs))
// and provides functions such as OppositeDir(), Letter() ('U'), Word() ('UP'),
// etc.
namespace direction {
extern int shift[4][2];
extern char letter[4];
}

class Pos {
 public:
  Pos() : Pos(0, 0) {}
  Pos(int x, int y) : x_(x), y_(y) {}
  Pos move(int dir) {
    return Pos(x_ + direction::shift[dir][0], y_ + direction::shift[dir][1]);
  }
  int x() { return x_; }
  int y() { return y_; }

 private:
  int x_;
  int y_;
};

#endif  // OBJECTS_POS_H_
