#include "pieces.h"
#include "board/board.h"
#include "piece/static.h"

  qtc::pc::Rook::Rook(Board &game,
		      const unsigned short int position,
		      const bool isWhite)
    : mPosition(1ULL << position),
      mWhite(isWhite) {setNewPosition(*this, game, game.rookPositions);}

  void qtc::pc::Rook::movegen(const Board &game)
  {
    const unsigned short int position = log2(mPosition);

    unsigned long long int upperStep;
    for(unsigned short int i = 0; i < rookMoveTable.upper[position]; i++)
    {
      upperStep = mPosition << 8*(i+1);
      if(shiftMovesBlocked(*this, game, upperStep)) break;
    }

    unsigned long long int lowerStep;
    for(unsigned short int i = 0; i < rookMoveTable.lower[position]; i++)
    {
      lowerStep = mPosition >> 8*(i+1);
      if(shiftMovesBlocked(*this, game, lowerStep)) break;
    }

    unsigned long long int rightStep;
    for(unsigned short int i = 0; i < rookMoveTable.right[position]; i++)
    {
      rightStep = mPosition >> (i+1);
      if(shiftMovesBlocked(*this, game, rightStep)) break;
    }

    unsigned long long int leftStep;
    for(unsigned short int i = 0; i < rookMoveTable.left[position]; i++)
    {
      leftStep = mPosition << (i+1);
      if(shiftMovesBlocked(*this, game,  leftStep)) break;
    }

    removeIllegalMoves(*this, game);
  }

  void qtc::pc::Rook::move(Board &game, std::string desiredMove)
  {
    const unsigned short int numberMove =
      convertStringToPosition(desiredMove);
    const unsigned long long int binaryMove =
      binaryField[numberMove];
    
    if(isImpossible(*this, binaryMove))
    {
      std::cerr << "impossible move!" << std::endl;
      return;
    }

    const unsigned short int oldPosition = log2(mPosition);
    if(oldPosition == h1) game.whiteCanCastleShort = false;
    if(oldPosition == a1) game.whiteCanCastleLong  = false;
    if(oldPosition == h8) game.blackCanCastleShort = false;
    if(oldPosition == a8) game.blackCanCastleLong  = false;

    deletePiece(*this, game, game.rookPositions);   

    correctPiecePosition(*this, game, numberMove);
	
    mPosition = binaryMove;
    setNewPosition(*this, game, game.rookPositions);

    deletePieceFromHitPosition(*this, game);

    game.whiteToMove = !game.whiteToMove;
  }
