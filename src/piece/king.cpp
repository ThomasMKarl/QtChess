#include "pieces.h"
#include "board/board.h"
#include "piece/static.h"

  qtc::pc::King::King(Board &game,
		      const unsigned short int position,
		      const bool isWhite)
    : mPosition(1ULL << position),
      mWhite(isWhite) {setNewPosition(*this, game, game.kingPositions);}
  
  void qtc::pc::King::movegen(const Board &game)
  {
    const unsigned short int position = log2(mPosition);
    
    if(mWhite)
      mPossibleMoves |= pow2(kingMoveTable[position]) | game.whitePositions;
    else
      mPossibleMoves |= pow2(kingMoveTable[position]) | game.blackPositions;

    const unsigned long long int allPositions =
      game.whitePositions | game.blackPositions;

    unsigned long long int fieldsBetweenKingAndRook =
      0b110;
    if(mWhite  && game.whiteCanCastleShort &&
       (fieldsBetweenKingAndRook & allPositions) &&
       !game.whiteIsChecked &&
       (fieldsBetweenKingAndRook & game.threatenedFields))
      mPossibleMoves |= pow2(g1);
    
    fieldsBetweenKingAndRook =
      0b1110000;
    if(mWhite  && game.whiteCanCastleLong  &&
       (fieldsBetweenKingAndRook & allPositions) &&
       !game.whiteIsChecked &&
       (fieldsBetweenKingAndRook & game.threatenedFields)) 
      mPossibleMoves |= pow2(c1);
    
    fieldsBetweenKingAndRook =
      0b0000011000000000000000000000000000000000000000000000000000000000;
    if(!mWhite && game.blackCanCastleShort &&
       (fieldsBetweenKingAndRook & allPositions) &&
       !game.blackIsChecked &&
       (fieldsBetweenKingAndRook & game.threatenedFields))
      mPossibleMoves |= pow2(g8);
    
    fieldsBetweenKingAndRook =
      0b0111000000000000000000000000000000000000000000000000000000000000;
    if(!mWhite && game.blackCanCastleLong  &&
       (fieldsBetweenKingAndRook & allPositions) &&
       !game.blackIsChecked &&
       (fieldsBetweenKingAndRook & game.threatenedFields))
      mPossibleMoves |= pow2(c8);

    removeIllegalMoves(*this, game);
  }
  
  void qtc::pc::King::move(Board &game, std::string desiredMove)
  {
    const unsigned short int numberMove =
      convertStringToPosition(desiredMove);
    const unsigned long long int binaryMove =
      binaryField[numberMove];
    
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
    
    if(isImpossible(*this, binaryMove))
    {
      std::cerr << "impossible move!" << std::endl;
      return;
    }

    correctRook(game, numberMove);
   
    deletePiece(*this, game, game.kingPositions);     

    correctPiecePosition(*this, game, numberMove);
    
    mPosition = binaryMove;
    setNewPosition(*this, game, game.kingPositions);

    deletePieceFromHitPosition(*this, game);

    game.whiteToMove = !game.whiteToMove;
  }

void qtc::pc::King::correctRook(Board &game, const unsigned short int numberMove)
  {
    if(numberMove == g1)
    {
      auto extractedPiece = game.pieces.extract(h1);
      extractedPiece.key() = f1;
      game.pieces.insert(std::move(extractedPiece));
      mpark::get<Rook>(game.pieces.at(f1)).setPosition(f1);
      
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
      mpark::get<Rook>(game.pieces.at(d1)).setPosition(d1);
      
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
      mpark::get<Rook>(game.pieces.at(f8)).setPosition(f8);
      
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
      mpark::get<Rook>(game.pieces.at(d8)).setPosition(d8);
      
      game.rookPositions  =  game.rookPositions & ~binaryField[a8];
      game.blackPositions = game.blackPositions & ~binaryField[a8];

      game.rookPositions  |= binaryField[d8];
      game.blackPositions |= binaryField[d8];
    }
  }
