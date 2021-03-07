#include "piece/king.h"

  King::King(Board &game, unsigned short int position, bool isWhite)
  : Piece(position, isWhite)
  {
    setNewPosition(game, game.kingPositions);
    
    if(mWhite)
      pathToImage = "img/wking.png";
    else
      pathToImage = "img/bking.png";
  }
  
  void King::movegen(Board &game)
  {
    unsigned short int position = log2(mPosition);
    
    if(mWhite)
      mPossibleMoves |= pow2(kingMoveTable[position]) | game.whitePositions;
    else
      mPossibleMoves |= pow2(kingMoveTable[position]) | game.blackPositions;

    unsigned long long int allPositions = game.whitePositions | game.blackPositions;
    
    if(mWhite  && game.whiteCanCastleShort &&
       (0b110 & allPositions) &&
       !game.whiteIsChecked &&
       (0b110 & game.threatenedFields))
      mPossibleMoves |= pow2(g1);

    if(mWhite  && game.whiteCanCastleLong  &&
       (0b1110000 & allPositions) &&
       !game.whiteIsChecked &&
       (0b1110000 & game.threatenedFields)) 
      mPossibleMoves |= pow2(c1);
    
    if(!mWhite && game.blackCanCastleShort &&
       (0b0000011000000000000000000000000000000000000000000000000000000000 & allPositions) &&
       !game.blackIsChecked &&
       (0b0000011000000000000000000000000000000000000000000000000000000000 & game.threatenedFields))
      mPossibleMoves |= pow2(g8);
    
    if(!mWhite && game.blackCanCastleLong  &&
       (0b0111000000000000000000000000000000000000000000000000000000000000 & allPositions) &&
       !game.blackIsChecked &&
       (0b0111000000000000000000000000000000000000000000000000000000000000 & game.threatenedFields))
      mPossibleMoves |= pow2(c8);

    removeIllegalMoves(game);
  }
  
  void King::move(Board &game, std::string desiredMove)
  {
    unsigned short int numberMove =
      convertStringToPosition(desiredMove);
    unsigned long long int binaryMove = binaryField[numberMove];
    
    if(mWhite)
    {
      game.whiteCanCastleLong  = false;
      game.whiteCanCastleShort = false;
    }
    else
    {
      game.blackCanCastleLong  = false;
      game.blackCanCastleShort = false;
    }
    
    if(isImpossible(binaryMove))
    {
      std::cerr << "impossible move!" << std::endl;
      return;
    }

    correctRook(game, numberMove);
   
    deletePiece(game, game.kingPositions);     

    correctPiecePosition(game, numberMove);
    
    mPosition = binaryMove;
    setNewPosition(game, game.kingPositions);

    deletePieceFromHitPosition(game);

    game.whiteToMove = !game.whiteToMove;
  }

  void King::correctRook(Board &game, unsigned short int numberMove)
  {
    if(numberMove == g1)
    {
      auto extractedPiece = game.pieces.extract(h1);
      extractedPiece.key() = f1;
      game.pieces.insert(std::move(extractedPiece));
      game.pieces.at(f1)->setPosition(f1);
      
      game.rookPositions  =  game.rookPositions & ~binaryField[h1];
      game.whitePositions = game.whitePositions & ~binaryField[h1];

      game.rookPositions  |= binaryField[f1];
      game.whitePositions |= binaryField[f1];
    }
    if(numberMove == c1)
    {
      auto extractedPiece = game.pieces.extract(a1);
      extractedPiece.key() = d1;
      game.pieces.insert(std::move(extractedPiece));
      game.pieces.at(d1)->setPosition(d1);
      
       game.rookPositions =  game.rookPositions & ~binaryField[a1];
      game.whitePositions = game.whitePositions & ~binaryField[a1];

      game.rookPositions  |= binaryField[d1];
      game.whitePositions |= binaryField[d1];
    }
    if(numberMove == g8)
    {
      auto extractedPiece = game.pieces.extract(h8);
      extractedPiece.key() = f8;
      game.pieces.insert(std::move(extractedPiece));
      game.pieces.at(f8)->setPosition(f8);
      
      game.rookPositions  =  game.rookPositions & ~binaryField[h8];
      game.blackPositions = game.blackPositions & ~binaryField[h8];

      game.rookPositions  |= binaryField[f8];
      game.blackPositions |= binaryField[f8];
    }
    if(numberMove == c8)
    {
      auto extractedPiece = game.pieces.extract(a8);
      extractedPiece.key() = d8;
      game.pieces.insert(std::move(extractedPiece));
      game.pieces.at(d8)->setPosition(d8);
      
      game.rookPositions  =  game.rookPositions & ~binaryField[a8];
      game.blackPositions = game.blackPositions & ~binaryField[a8];

      game.rookPositions  |= binaryField[d8];
      game.blackPositions |= binaryField[d8];
    }
  }
