#include "piece/bishop.h"

  qtc::pc::Bishop::Bishop(qtc::Board &game,
			  const unsigned short int position,
			  const bool isWhite)
    : Piece(position, isWhite)
  { 
    setNewPosition(game, game.bishopPositions);
    
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

  void qtc::pc::Bishop::move(qtc::Board &game, std::string desiredMove)
  {
    const unsigned short int numberMove =
      convertStringToPosition(desiredMove);
    const unsigned long long int binaryMove = binaryField[numberMove];

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
