#include "piece/bishop.h"

  Bishop::Bishop(Board &game, unsigned short int position, bool isWhite)
  : Piece(position, isWhite)
  { 
    setNewPosition(game, game.bishopPositions);
    
    if(mWhite)
      pathToImage = "img/wbishop.png";
    else
      pathToImage = "img/bbishop.png";
  }

  void Bishop::movegen(Board &game)
  {
    unsigned short int position = log2(mPosition);
    mPossibleMoves = 0;
    
    unsigned long long int upperLeftStep;
    for(unsigned short int i = 0; i < bishopMoveTable.upperLeft[position];  i++)
    {
      upperLeftStep = mPosition << 9*(i+1);
      if(shiftMovesBlocked(game, upperLeftStep)) break;
    }
    
    unsigned long long int lowerRightStep;
    for(unsigned short int i = 0; i < bishopMoveTable.lowerRight[position]; i++)
    {
      lowerRightStep = mPosition >> 9*(i+1);
      if(shiftMovesBlocked(game, lowerRightStep)) break;
    }
 
    unsigned long long int upperRightStep;
    for(unsigned short int i = 0; i < bishopMoveTable.upperRight[position]; i++)
    {
      upperRightStep = mPosition << 7*(i+1);
      if(shiftMovesBlocked(game, upperRightStep)) break;
    }
 
    unsigned long long int lowerLeftStep;
    for(unsigned short int i = 0; i < bishopMoveTable.lowerLeft[position];  i++)
    {
      lowerLeftStep = mPosition >> 7*(i+1);
      if(shiftMovesBlocked(game, lowerLeftStep)) break;
    }

    removeIllegalMoves(game);
  }

  void Bishop::move(Board &game, std::string desiredMove)
  {
    unsigned short int numberMove =
      convertStringToPosition(desiredMove);
    unsigned long long int binaryMove = binaryField[numberMove];

    if(isImpossible(binaryMove))
    {
      std::cerr << "impossible move!" << std::endl;
      return;
    }
    
    deletePiece(game, game.bishopPositions);     

    correctPiecePosition(game, numberMove);
    
    mPosition = binaryMove;
    setNewPosition(game, game.bishopPositions);

    deletePieceFromHitPosition(game);

    game.whiteToMove = !game.whiteToMove;
  }
