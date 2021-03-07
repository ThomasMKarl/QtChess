#ifndef PIECE_H
#define PIECE_H

#include "board.h"


class Piece
{
 public:
  explicit Piece(unsigned short int position, bool isWhite)
  : mPosition(1ULL << position), mWhite(isWhite) {};
  
  virtual ~Piece(){};
  virtual void movegen(Board&) {};
  virtual void move(Board&, std::string) {};
  
  unsigned short int getPosition() const {return log2(mPosition);}
  void setPosition(unsigned short int position) {mPosition = pow2(position);}
  unsigned long long int getPossibleMoves() const {return mPossibleMoves;}
  bool isWhite() const {return mWhite;}
  virtual void setCanHitEpLeft()  {};
  virtual void setCanHitEpRight() {};

  bool isImpossible(unsigned long long int move)
  {
    return !(move & mPossibleMoves);
  }

  std::string pathToImage{};

 protected:
  unsigned long long int mPosition{0};
  unsigned long long int mPossibleMoves{0};
  bool mWhite{true};

  void setNewPosition(Board &game, unsigned long long int &positions)
  {
    positions |= mPosition;
    
    if(mWhite)
      game.whitePositions |= mPosition;
    else
      game.blackPositions |= mPosition;
  }

  void deletePiece(Board &game, unsigned long long int &positions)
  {
    positions &= ~mPosition;
    
    if(mWhite)
      game.whitePositions &= ~mPosition;
    else
      game.blackPositions &= ~mPosition;
  }

  void deletePieceFromHitPosition(Board &game)
  {
    game.pawnPositions   &= ~mPosition;
    game.knightPositions &= ~mPosition;
    game.bishopPositions &= ~mPosition;
    game.rookPositions   &= ~mPosition;
    game.queenPositions  &= ~mPosition;
    
    game.whitePositions  &= ~mPosition;
    game.blackPositions  &= ~mPosition;
  }

  bool shiftMovesBlocked(Board &game, unsigned long long int shift)
  {
    if(mWhite && (shift & game.whitePositions) != 0)
      return true;
      
    if(mWhite && (shift & game.blackPositions) != 0)
    {
      mPossibleMoves |= shift;
      return true;
    }

    if(!mWhite && (shift & game.blackPositions) != 0)
      return true;
      
    if(!mWhite && (shift & game.whitePositions) != 0)
    {
      mPossibleMoves |= shift;
      return true;
    }
    
    mPossibleMoves |= shift;
    return false;
  }

  void correctPiecePosition(Board &game, unsigned short int newPosition)
  {
    short int oldPosition = log2(mPosition);
    
    game.pieces.erase(newPosition);
    
    auto extractedPiece = game.pieces.extract(oldPosition);
    extractedPiece.key() = newPosition;
    game.pieces.insert(std::move(extractedPiece));
  }

  void removeIllegalMoves(Board &game)
  {
    std::bitset<sizeof(unsigned long long int) * CHAR_BIT> bit(mPossibleMoves);
    unsigned long long int threatenedFields;

    for(unsigned short int b = 0; b < 64; b++)
    {
      if(bit[b] == 1)
      {
	Board gameCopy = game;
        gameCopy.pieces.at( log2(mPosition) ) ->move( gameCopy,fieldMap[b] );
        if(mWhite)
	{
	  threatenedFields = gameCopy.generateBlackMoves();
	  if(threatenedFields &
	     gameCopy.kingPositions &
	     gameCopy.whitePositions)
	    bit.reset(b);
	}
        else
	{
	  threatenedFields = gameCopy.generateWhiteMoves();
	  if(threatenedFields &
	     gameCopy.kingPositions &
	     gameCopy.blackPositions)
	    bit.reset(b);
	}
      }
    }

    mPossibleMoves = bit.to_ullong();
  }
};

#endif
