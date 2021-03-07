#ifndef KING_H
#define KING_H

#include "board.h"
#include "piece/piece.h"


class King: public Piece
{
 public:
  explicit King(Board &game, unsigned short int position, bool isWhite);
  
  void movegen(Board &game) final;
  void move(Board &game, std::string desiredMove) final;

  void correctRook(Board &game, unsigned short int numberMove);
};

#endif
