#ifndef QUEEN_H
#define QUEEN_H

#include "board.h"
#include "piece/piece.h"


class Queen: public Piece
{
 public:
  explicit Queen(Board &game, unsigned short int position, bool isWhite);
  
  void movegen(Board &game) final;
  void move(Board &game, std::string desiredMove) final;
};

#endif
