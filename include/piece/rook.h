#ifndef ROOK_H
#define ROOK_H

#include "board.h"
#include "piece/piece.h"


class Rook: public Piece
{
 public:
  explicit Rook(Board &game, unsigned short int position, bool isWhite);

  void movegen(Board &game) final;
  void move(Board &game, std::string desiredMove) final;
};

#endif
