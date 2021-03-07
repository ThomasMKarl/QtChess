#include "piece/pawn.h"

  Pawn::Pawn(Board &game, unsigned short int position, bool isWhite)
  : Piece(position, isWhite), hasMoved(false), canHitEpLeft(false), canHitEpRight(false)
  {
    setNewPosition(game, game.pawnPositions);
    
    if(mWhite)
      pathToImage = "img/wpawn.png";
    else
      pathToImage = "img/bpawn.png";
  }

  void Pawn::movegen(Board &game)
  {
    unsigned long long int hit{0};
    unsigned long long int onestep{0};
    unsigned long long int doublestep{0};
    unsigned long long int allPositions =
      game.blackPositions | game.whitePositions;

    std::bitset<64> pawnBits(allPositions);
    std::cout << pawnBits;exit(1);
	  
    if(mWhite)
    {
      onestep = mPosition << 8 | allPositions;
      
      if(!hasMoved) doublestep = onestep << 8 | allPositions;

      hit = mPosition << 7 & game.blackPositions &
            mPosition << 9 & game.blackPositions;

      if(canHitEpLeft  &&
	 mPosition >= binaryField[32] &&
	 mPosition <= binaryField[39])
	hit |= mPosition << 9;
      if(canHitEpRight &&
	 mPosition >= binaryField[32] &&
	 mPosition <= binaryField[39])
	hit |= mPosition << 7;
    }
    else
    {
      onestep = mPosition >> 8 | allPositions;

      if(!hasMoved) doublestep = onestep >> 8 | allPositions;
      
      hit = mPosition >> 7 & game.whitePositions &
            mPosition >> 9 & game.whitePositions;

      if(canHitEpLeft  &&
	 mPosition >= binaryField[24] &&
	 mPosition <= binaryField[31])
	hit |= mPosition >> 9;
      if(canHitEpRight &&
	 mPosition >= binaryField[24] &&
	 mPosition <= binaryField[31])
	hit |= mPosition >> 7;
    }    
 
    mPossibleMoves = onestep | doublestep | hit;

    canHitEpLeft  = false;
    canHitEpRight = false;

    removeIllegalMoves(game);
  }

  void Pawn::move(Board &game, std::string desiredMove)
  {
    unsigned short int numberMove =
      convertStringToPosition(desiredMove);
    unsigned long long int binaryMove = binaryField[numberMove];
    
    if(isImpossible(binaryMove))
    {
      std::cerr << "impossible move!" << std::endl;
      return;
    }

    unsigned short int oldPosition = log2(mPosition);
    if( abs(numberMove-oldPosition) == 16)
    {
      if(game.pawnPositions & binaryField[numberMove+1])
	game.pieces.at(numberMove+1)->setCanHitEpLeft();
      if(game.pawnPositions & binaryField[numberMove-1])
        game.pieces.at(numberMove-1)->setCanHitEpRight();
    } 
    
    PromotionPiece promoteTo = none;
    unsigned short int offboard = 64;
    if(numberMove >= h8 || numberMove <= a1) switch(desiredMove[2])
    {
      case 'N':
	game.createPiece<Knight>(offboard, mWhite);
	promoteTo = knight;
	break;
      case 'B':
	game.createPiece<Bishop>(offboard, mWhite);
	promoteTo = bishop;
	break;
      case 'Q':
	game.createPiece<Queen >(offboard, mWhite);
	promoteTo =  queen;
	break;
      case 'R':
	game.createPiece<Rook  >(offboard, mWhite);
	promoteTo =   rook;
	break;
      default:
	std::cerr << "impossible move!" << std::endl;
        return;
    }
       
    deletePiece(game, game.pawnPositions);

    removeEpPawn(game, numberMove);

    correctPiecePosition(game, numberMove);
    
    mPosition = binaryMove;

    deletePieceFromHitPosition(game);

    hasMoved = true;
    game.whiteToMove = !game.whiteToMove;

    if(promoteTo != none)
      promote(game, promoteTo);
    else
      setNewPosition(game, game.pawnPositions);   
  }

  void Pawn::promote(Board &game, PromotionPiece promoteTo)
  {
    switch(promoteTo)
    {
      case knight:
	setNewPosition(game, game.knightPositions); 
	break;
      case bishop:
	setNewPosition(game, game.bishopPositions);
	break;
      case queen:
	setNewPosition(game, game.queenPositions );
	break;
      case rook:
	setNewPosition(game, game.rookPositions  );
	break;
      default:
	std::cerr << "could not promote!";
        return;
    }
	
    unsigned short int position = log2(mPosition);
    unsigned short int offboard = 64;
    auto extractedPawn        = game.pieces.extract(position);
    auto pieceAfterPromotions = game.pieces.extract(offboard);
    
    pieceAfterPromotions.key() = position;
    game.pieces.insert(std::move(pieceAfterPromotions));

    if(mWhite)
      game.whitePositions |= mPosition;
    else
      game.blackPositions |= mPosition;
  }

  void Pawn::removeEpPawn(Board &game, unsigned short int numberMove)
  {
    unsigned short int oldPosition = log2(mPosition);
    
    unsigned long long int binaryMove = binaryField[numberMove];
    unsigned long long int allPositions =
      game.blackPositions | game.whitePositions;
    
    if( abs(numberMove-oldPosition) == 7 && (allPositions | binaryMove) )
    {
      game.pieces.erase(numberMove-1);

      mPosition = numberMove-1;
      deletePieceFromHitPosition(game);
    }
    if( abs(numberMove-oldPosition) == 9 && (allPositions | binaryMove) )
    {
      game.pieces.erase(numberMove+1);
      
      mPosition = numberMove+1;
      deletePieceFromHitPosition(game);
    }
    
    setPosition(oldPosition);
  }
