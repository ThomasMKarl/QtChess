#ifndef PAWN_H
#define PAWN_H

#include "stdlib.h"
#include "def.h"


namespace qtc {

class Board;
  
namespace pc {

enum PromotionPiece
{
  none   =  0,
  knight =  1,
  bishop =  2,
  queen  =  3,
  rook   =  4
};

class Pawn
{
 public:
  explicit Pawn(Board &game,
		const unsigned short int position,
		const bool isWhite);

  void movegen(const Board &game);
  void move(Board &game, std::string desiredMove);
  
  void promote(Board &game, const PromotionPiece promoteTo);
  void removeEpPawn(Board &game, const unsigned short int numberMove);
  void setCanHitEpLeft()  {canHitEpLeft  = true;}
  void setCanHitEpRight() {canHitEpRight = true;}

  unsigned short int getPosition() const
    {return log2(mPosition);}
  void setPosition(const unsigned short int position)
    {mPosition = 1ULL << position;}
  unsigned long long int getPossibleMoves() const
    {return mPossibleMoves;}
  void setPossibleMoves(unsigned long long int possibleMoves)
    {mPossibleMoves = possibleMoves;}
  bool isWhite() const
    {return mWhite;}

  std::string pathToImage{};

 private:
  unsigned long long int mPosition{0};
  unsigned long long int mPossibleMoves{0};
  bool mWhite{true};

  bool hasMoved{false};
  bool canHitEpLeft{false};
  bool canHitEpRight{false};
};

};};

#endif
