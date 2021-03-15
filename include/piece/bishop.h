#ifndef BISHOP_H
#define BISHOP_H

#include "stdlib.h"
#include "def.h"

namespace qtc {

class Board;

namespace pc {

class Bishop
{
 public:
  explicit Bishop(Board &game,
		  const unsigned short int position,
		  const bool isWhite);
  
  void movegen(const Board &game);
  void move(Board &game, std::string desiredMove);

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
};

};};

#endif
