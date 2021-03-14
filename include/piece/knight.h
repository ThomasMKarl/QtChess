#ifndef KNIGHT_H
#define KNIGHT_H

#include "board/board.h"
#include "piece/piece.h"


namespace qtc {
namespace pc {

class Knight: public Piece
{
 public:
  explicit Knight(Board &game, const unsigned short int position, const bool isWhite);
  
  void movegen(const Board &game) final;
  void move(Board &game, std::string desiredMove) final;
};

};};

#endif
