#ifndef OBJECTS_SERVER_MOVE_H_
#define OBJECTS_SERVER_MOVE_H_

#include "pos.h"

class ServerMove {
 public:
  enum MoveType { kEatCandy, kMove };

  static ServerMove EatCandy(int turn) {
    ServerMove move;
    move.move_type_ = MoveType::kEatCandy;
    move.turn_id_ = turn;
    return move;
  }
  static ServerMove Move(int turn, Pos pos) {
    ServerMove move;
    move.move_type_ = MoveType::kMove;
    move.turn_id_ = turn;
    move.move_to_pos_ = pos;
    return move;
  }
  MoveType get_move_type() const { return move_type_; }
  int get_turn_id() const { return turn_id_; }
  Pos get_move_to_pos() const { return move_to_pos_; }

 private:
  MoveType move_type_;
  int turn_id_ = -1;
  Pos move_to_pos_;
};

#endif  // OBJECTS_SERVER_MOVE_H_
