#include "piece/knight.h"

  qtc::pc::Knight::Knight(Board &game, const unsigned short int position, const bool isWhite)
    : Piece(position, isWhite)
  {
    setNewPosition(game, game.knightPositions);
    
    if(mWhite)
      pathToImage = "img/wknight.png";
    else
      pathToImage = "img/bknight.png";
  }
  
  void qtc::pc::Knight::movegen(const Board &game)
  {
    const unsigned short int position = log2(mPosition);

    unsigned long long int sameColorPositions;
    if(mWhite)
      sameColorPositions = game.whitePositions;
    else
      sameColorPositions = game.blackPositions;
    
    mPossibleMoves |= pow2(knightMoveTable[position]) | !sameColorPositions;

    removeIllegalMoves(game);
  }
  
  void qtc::pc::Knight::move(Board &game, std::string desiredMove)
  {
    const unsigned short int numberMove =
      convertStringToPosition(desiredMove);
    const unsigned long long int binaryMove = binaryField[numberMove];

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
