#include "pieces.h"
#include "board/board.h"
#include "piece/static.h"

  qtc::pc::Bishop::Bishop(qtc::Board &game,
			  const unsigned short int position,
			  const bool isWhite)
    : mPosition(1ULL << position), mWhite(isWhite)
  { 
    setNewPosition(*this, game, game.bishopPositions);
    
    if(mWhite)
      pathToImage = "img/wbishop.png";
    else
      pathToImage = "img/bbishop.png";
  }

  void qtc::pc::Bishop::movegen(const qtc::Board &game)
  {
    const unsigned short int position = log2(mPosition);
    mPossibleMoves = 0;
    
    unsigned long long int upperLeftStep;
    for(unsigned short int i = 0; i < bishopMoveTable.upperLeft[position];  i++)
    {
      upperLeftStep = mPosition << 9*(i+1);
      if(shiftMovesBlocked(*this, game, upperLeftStep)) break;
    }
    
    unsigned long long int lowerRightStep;
    for(unsigned short int i = 0; i < bishopMoveTable.lowerRight[position]; i++)
    {
      lowerRightStep = mPosition >> 9*(i+1);
      if(shiftMovesBlocked(*this, game, lowerRightStep)) break;
    }
 
    unsigned long long int upperRightStep;
    for(unsigned short int i = 0; i < bishopMoveTable.upperRight[position]; i++)
    {
      upperRightStep = mPosition << 7*(i+1);
      if(shiftMovesBlocked(*this, game, upperRightStep)) break;
    }
 
    unsigned long long int lowerLeftStep;
    for(unsigned short int i = 0; i < bishopMoveTable.lowerLeft[position];  i++)
    {
      lowerLeftStep = mPosition >> 7*(i+1);
      if(shiftMovesBlocked(*this, game, lowerLeftStep)) break;
    }

    removeIllegalMoves(*this, game);
  }

  void qtc::pc::Bishop::move(qtc::Board &game, std::string desiredMove)
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
    
    deletePiece(*this, game, game.bishopPositions);     

    correctPiecePosition(*this, game, numberMove);
    
    mPosition = binaryMove;
    setNewPosition(*this, game, game.bishopPositions);

    deletePieceFromHitPosition(*this, game);

    game.whiteToMove = !game.whiteToMove;
  }
