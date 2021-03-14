#ifndef BISHOP_H
#define BISHOP_H

#include "board/board.h"
#include "piece/piece.h"

namespace qtc {
namespace pc {

class Bishop: public Piece
{
 public:
  explicit Bishop(Board &game,
		  const unsigned short int position,
		  const bool isWhite);
  
  void movegen(const Board &game) final;
  void move(Board &game, std::string desiredMove) final;
};

};};

#endif
