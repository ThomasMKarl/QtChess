#ifndef KNIGHT_H
#define KNIGHT_H

#include "board.h"
#include "piece/piece.h"


class Knight: public Piece
{
 public:
  explicit Knight(Board &game, unsigned short int position, bool isWhite);
  
  void movegen(Board &game) final;
  void move(Board &game, std::string desiredMove) final;
};

#endif
