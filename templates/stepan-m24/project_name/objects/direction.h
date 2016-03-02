#ifndef OBJECTS_DIRECTION_H_
#define OBJECTS_DIRECTION_H_

#include <string>

#include <SFML/Graphics.hpp>

struct Direction {
 public:
  Direction() : Direction(0) {}
  Direction(int d);
  int dir() const { return dir_; }
  bool valid() const { return valid_; }
  static Direction Invalid();
  static Direction FromChar(char c);
  static Direction FromWord(const std::string& word);
  static Direction FromKey(sf::Keyboard::Key key);
  char Letter();
  std::string Word();
  sf::Keyboard::Key Key();
  Direction ShiftCounterclockwise(int by){ return Direction(dir_ + by); }
  Direction ShiftClockwise(int by) { return ShiftClockwise(-by); }
  Direction Opposite() { return ShiftClockwise(2); }
  Direction NextCounterlockwise() { return ShiftCounterclockwise(1); }
  Direction NextClockwise() { return ShiftClockwise(1); }
  int* Shift() { return dir_to_shift_[dir_]; }

 private:
  short int dir_;
  bool valid_;
  static std::string dir_to_string_[4];
  static int dir_to_shift_[4][2];
};
#endif  // OBJECTS_DIRECTION_H_
