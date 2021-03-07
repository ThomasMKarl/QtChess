#include "piece/knight.h"

  Knight::Knight(Board &game, unsigned short int position, bool isWhite)
  : Piece(position, isWhite)
  {
    setNewPosition(game, game.knightPositions);
    
    if(mWhite)
      pathToImage = "img/wknight.png";
    else
      pathToImage = "img/bknight.png";
  }
  
  void Knight::movegen(Board &game)
  {
    unsigned short int position = log2(mPosition);

    unsigned long long int sameColorPositions;
    if(mWhite)
      sameColorPositions = game.whitePositions;
    else
      sameColorPositions = game.blackPositions;
    
    mPossibleMoves |= pow2(knightMoveTable[position]) | !sameColorPositions;

    removeIllegalMoves(game);
  }
  
  void Knight::move(Board &game, std::string desiredMove)
  {
    unsigned short int numberMove =
      convertStringToPosition(desiredMove);
    unsigned long long int binaryMove = binaryField[numberMove];

    if(isImpossible(binaryMove))
    {
      std::cerr << "impossible move!" << std::endl;
      return;
    }
    
    deletePiece(game, game.knightPositions);   

    correctPiecePosition(game, numberMove);
    
    mPosition = binaryMove;
    setNewPosition(game, game.knightPositions);

    deletePieceFromHitPosition(game);

    game.whiteToMove = !game.whiteToMove;
  }
