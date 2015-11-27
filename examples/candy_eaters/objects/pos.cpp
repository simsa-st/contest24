#include "pos.h"
int direction::shift[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
char direction::letter[4] = {'L', 'D', 'R', 'U'};

std::string Pos::Print() const {
  return "pos<" + std::to_string(x_) + "," + std::to_string(y_) + ">";
}
