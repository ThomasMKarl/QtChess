#ifndef PAWN_H
#define PAWN_H

#include "board.h"
#include "piece/piece.h"


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
  explicit Pawn(Board &game, unsigned short int position, bool isWhite);

  void movegen(Board &game) final;
  void move(Board &game, std::string desiredMove) final;
  void promote(Board &game, PromotionPiece promoteTo);
  void removeEpPawn(Board &game, unsigned short int numberMove);
  void setCanHitEpLeft()  final {canHitEpLeft  = true;}
  void setCanHitEpRight() final {canHitEpRight = true;}
  
 private:
  bool hasMoved{false};
  bool canHitEpLeft{false};
  bool canHitEpRight{false};
  
};

#endif
