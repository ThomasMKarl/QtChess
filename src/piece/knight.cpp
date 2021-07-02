#include "pieces.h"
#include "board/board.h"
#include "piece/static.h"

  qtc::pc::Knight::Knight(Board &game,
			  const unsigned short int position,
			  const bool isWhite)
    : mPosition(1ULL << position),
      mWhite(isWhite) {setNewPosition(*this, game, game.knightPositions);}
  
  void qtc::pc::Knight::movegen(const Board &game)
  {
    const unsigned short int position = log2(mPosition);

    unsigned long long int allPositions;
    if(mWhite)
      allPositions = game.whitePositions;
    else
      allPositions = game.blackPositions;
    
    mPossibleMoves |= pow2(knightMoveTable[position]) | !allPositions;

    removeIllegalMoves(*this, game);
  }
  
  void qtc::pc::Knight::move(Board &game, std::string desiredMove)
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
    
    deletePiece(*this, game, game.knightPositions);   

    correctPiecePosition(*this, game, numberMove);
    
    mPosition = binaryMove;
    setNewPosition(*this, game, game.knightPositions);

    deletePieceFromHitPosition(*this, game);

    game.whiteToMove = !game.whiteToMove;
  }
