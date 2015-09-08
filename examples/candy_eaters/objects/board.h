#ifndef OBJECTS_BOARD_H_
#define OBJECTS_BOARD_H_

#include <vector>

#include "pos.h"

// Rectangular board where the individual cells can hold arbitrary type (that
// vector can hold).
template <typename CellType>
class Board {
 public:
  // Empty board.
  Board() : Board(0) {}
  // Square board filled with CellType() default constructor values.
  Board(int board_size);
  // Rectangular board filled with CellType() default constructor values.
  Board(int board_size_x, int board_size_y);
  Board(const std::vector<std::vector<CellType>>& board);

  // Is this position inside the board.
  bool inside(Pos pos) const;

  // Access the cell at specified position.
  const CellType& operator[](Pos at) const { return board_[at.x()][at.y()]; }
  CellType& operator[](Pos at) { return board_[at.x()][at.y()]; }

  // Some accessors for entire board/rows.
  const std::vector<std::vector<CellType>>& const_board() const {
    return board_;
  }
  std::vector<std::vector<CellType>>& mutable_board() { return board_; }
  const std::vector<CellType>& const_row(int at) const { return board_[at]; }
  std::vector<CellType>& mutable_row(int at) { return board_[at]; }

 private:
  int board_size_[2];
  std::vector<std::vector<CellType>> board_;
};

template <typename CellType>
Board<CellType>::Board(int board_size)
    : Board(board_size, board_size) {}

template <typename CellType>
Board<CellType>::Board(int board_size_x, int board_size_y)
    : Board(std::vector<std::vector<CellType>>(
          board_size_x, std::vector<CellType>(board_size_y, CellType()))) {}

template <typename CellType>
Board<CellType>::Board(const std::vector<std::vector<CellType>>& board)
    : board_(board) {
  board_size_[0] = board.size();
  if (board_size_[0] == 0) {
    board_size_[1] = 0;
  } else {
    board_size_[1] = board[0].size();
  }
}

template <typename CellType>
bool Board<CellType>::inside(Pos pos) const {
  bool ins = pos.x() >= 0 && pos.x() < board_size_[0] && pos.y() >= 0 &&
             pos.y() < board_size_[1];
  return ins;
}

#endif  // OBJECTS_BOARD_H_
