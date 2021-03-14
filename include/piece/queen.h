#ifndef QUEEN_H
#define QUEEN_H

#include "board/board.h"
#include "piece/piece.h"


namespace qtc {
namespace pc {

class Queen: public Piece
{
 public:
  explicit Queen(Board &game, const unsigned short int position, const bool isWhite);
  
  void movegen(const Board &game) final;
  void move(Board &game, std::string desiredMove) final;
};

};};

#endif
