#ifndef PAWN_H
#define PAWN_H

#include "board/board.h"
#include "piece/piece.h"


namespace qtc {
namespace pc {

enum PromotionPiece
{
  none   =  0,
  knight =  1,
  bishop =  2,
  queen  =  3,
  rook   =  4
};

class Pawn: public Piece
{
 public:
  explicit Pawn(Board &game, const unsigned short int position, const bool isWhite);

  void movegen(const Board &game) final;
  void move(Board &game, std::string desiredMove) final;
  void promote(Board &game, const PromotionPiece promoteTo);
  void removeEpPawn(Board &game, const unsigned short int numberMove);
  void setCanHitEpLeft()  final {canHitEpLeft  = true;}
  void setCanHitEpRight() final {canHitEpRight = true;}
  
 private:
  bool hasMoved{false};
  bool canHitEpLeft{false};
  bool canHitEpRight{false};
};

};};

#endif
