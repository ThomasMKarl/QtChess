#include "piece/queen.h"

  qtc::pc::Queen::Queen(Board &game, const unsigned short int position, const bool isWhite)
    : Piece(position, isWhite)
  {
    setNewPosition(game, game.queenPositions);
    
    if(mWhite)
      pathToImage = "img/wqueen.png";
    else
      pathToImage = "img/bqueen.png";
  }
  
  void qtc::pc::Queen::movegen(const Board &game)
  {
    const unsigned short int position = log2(mPosition);
    mPossibleMoves = 0;
    
    //////////////////////////Bishop moves
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
    
    //////////////////////////Rook moves
    unsigned long long int upperStep;
    for(unsigned short int i = 0; i < rookMoveTable.upper[position]; i++)
    {
      upperStep = mPosition << 8*(i+1);
      if(shiftMovesBlocked(game, upperStep)) break;
    }
    
    unsigned long long int lowerStep;
    for(unsigned short int i = 0; i < rookMoveTable.lower[position]; i++)
    {
      lowerStep = mPosition >> 8*(i+1);
      if(shiftMovesBlocked(game, lowerStep)) break;
    }
 
    unsigned long long int rightStep;
    for(unsigned short int i = 0; i < rookMoveTable.right[position]; i++)
    {
      rightStep = mPosition >> (i+1);
      if(shiftMovesBlocked(game, rightStep)) break;
    }
 
    unsigned long long int leftStep;
    for(unsigned short int i = 0; i < rookMoveTable.left[position]; i++)
    {
      leftStep = mPosition << (i+1);
      if(shiftMovesBlocked(game, leftStep)) break;
    }

    removeIllegalMoves(game);
  };

  void qtc::pc::Queen::move(Board &game, std::string desiredMove)
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
