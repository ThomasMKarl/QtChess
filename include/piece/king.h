#ifndef KING_H
#define KING_H

#include "board/board.h"
#include "piece/piece.h"


namespace qtc {
namespace pc {

class King: public Piece
{
 public:
  explicit King(Board &game, const unsigned short int position, const bool isWhite);
  
  void movegen(const Board &game) final;
  void move(Board &game, std::string desiredMove) final;

  void correctRook(Board &game, const unsigned short int numberMove);
};

};};

#endif
