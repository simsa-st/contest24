#ifndef OBJECTS_BOARD_H_
#define OBJECTS_BOARD_H_

#include <vector>
#include <SFML/Graphics.hpp>

#include "pos.h"

template <typename CellType>
class Board;

// Iterator that iterates over all positions in selected board.
template <typename CellType>
class PosIterator : public Pos {
 public:
  PosIterator(const Board<CellType>* board, int x, int y)
      : Pos(x, y), board_(board) {}
  PosIterator& operator++() {
    if (y() + 1< board_->size(1)) {
      y_ += 1;
    } else {
      x_ += 1;
      y_ = 0;
    }
    return *this;
  }
  Pos operator*() { return *this; }
  bool operator!=(const PosIterator<CellType>& other) {
    return x() != other.x() || y() != other.y();
  }

 private:
  const Board<CellType>* board_;
};

// Rectangular board where the individual cells can hold arbitrary type (that
// vector can hold).
template <typename CellType>
class Board : public sf::Drawable, public sf::Transformable {
 public:
  // Empty board.
  Board() : Board(0) {}
  // Square board filled with CellType() default constructor values.
  Board(int board_size);
  // Rectangular board filled with CellType() default constructor values.
  Board(int board_size_x, int board_size_y);
  Board(const std::vector<std::vector<CellType>>& board);

  int size(int i) const { return board_size_[i]; }
  // Is this position inside the board.
  bool inside(const Pos& pos) const;

  // Access the cell at specified position.
  const CellType& operator[](const Pos& at) const { return board_[at.x()][at.y()]; }
  CellType& operator[](const Pos& at) { return board_[at.x()][at.y()]; }

  // Get a row to enable board[x][y].
  const std::vector<CellType>& operator[](int x) const { return board_[x]; }
  std::vector<CellType>& operator[](int x) { return board_[x]; }

  // Some accessors for entire board.
  const std::vector<std::vector<CellType>>& const_board() const {
    return board_;
  }
  std::vector<std::vector<CellType>>& mutable_board() { return board_; }

  // Iterators.
  typedef PosIterator<CellType> iterator;
  iterator begin() const { return PosIterator<CellType>(this, 0, 0); }
  iterator end() const { return PosIterator<CellType>(this, board_size_[0], 0); }

  // Draw this board.
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

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
  for (auto pos : *this) {
    board_[pos.x()][pos.y()].setPosition(pos.x(), pos.y());
  }
}

template <typename CellType>
bool Board<CellType>::inside(const Pos& pos) const {
  bool ins = pos.x() >= 0 && pos.x() < board_size_[0] && pos.y() >= 0 &&
             pos.y() < board_size_[1];
  return ins;
}

template <typename CellType>
void Board<CellType>::draw(sf::RenderTarget& target,
                           sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  for (Pos pos : *this) {
    target.draw(board_[pos.x()][pos.y()], states);
  }
}

#endif  // OBJECTS_BOARD_H_
