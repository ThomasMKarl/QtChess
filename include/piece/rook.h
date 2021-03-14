#ifndef ROOK_H
#define ROOK_H

#include "board/board.h"
#include "piece/piece.h"

namespace qtc {
namespace pc {

class Rook: public Piece
{
 public:
  explicit Rook(Board &game, const unsigned short int position, const bool isWhite);

  void movegen(const Board &game) final;
  void move(Board &game, std::string desiredMove) final;
};

};};

#endif
