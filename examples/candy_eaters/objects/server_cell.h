#ifndef OBJECTS_SERVER_CELL_H_
#define OBJECTS_SERVER_CELL_H_

struct ServerCell {
  ServerCell() : ServerCell(0) {}
  ServerCell(int candies) : num_candies(candies) {}
  int num_candies;
};

#endif  // OBJECTS_SERVER_CELL_H_
