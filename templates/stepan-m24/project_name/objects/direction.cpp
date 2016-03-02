#include "direction.h"

Direction::Direction(int d)
    : dir_((d >= 0) ? (d % 4) : (3 - (-d - 1) % 4)), valid_(true) {}

Direction Direction::Invalid() {
  Direction d;
  d.valid_ = false;
  return d;
}

Direction Direction::FromChar(char c) {
  for (int d = 0; d < 4; ++d) {
    if (dir_to_string_[d][0] == c) return Direction(d);
  }
  return Invalid();
}

Direction Direction::FromWord(const std::string& word) {
  if (word.length() == 0) return Invalid();
  return FromChar(word[0]);
}
Direction Direction::FromKey(sf::Keyboard::Key key) {
  switch (key) {
    case sf::Keyboard::Left: return Direction::FromChar('L');
    case sf::Keyboard::Up: return Direction::FromChar('U');
    case sf::Keyboard::Right: return Direction::FromChar('R');
    case sf::Keyboard::Down: return Direction::FromChar('D');
    default: return Invalid();
  }
}

char Direction::Letter() {
  return dir_to_string_[dir_][0];
}

std::string Direction::Word() {
  return dir_to_string_[dir_];
}

sf::Keyboard::Key Direction::Key() {
  switch(Letter()) {
    case 'L': return sf::Keyboard::Left;
    case 'U': return sf::Keyboard::Up;
    case 'R': return sf::Keyboard::Right;
    case 'D': return sf::Keyboard::Down;
    default: return sf::Keyboard::Unknown;
  }
}

std::string Direction::dir_to_string_[4] = {"Left", "Up", "Right", "Down"};
int Direction::dir_to_shift_[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
