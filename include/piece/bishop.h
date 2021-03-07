#ifndef BISHOP_H
#define BISHOP_H

#include "board.h"
#include "piece/piece.h"


class Bishop: public Piece
{
 public:
  explicit Bishop(Board &game, unsigned short int position, bool isWhite);
  
  void movegen(Board &game) final;
  void move(Board &game, std::string desiredMove) final;
};

#endif
