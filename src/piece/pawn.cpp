#include "pieces.h"
#include "board/board.h"
#include "piece/static.h"

  qtc::pc::Pawn::Pawn(Board &game, const unsigned short int position, const bool isWhite)
    : mPosition(1ULL << position),
      mWhite(isWhite),
      hasMoved(false),
      canHitEpLeft(false),
      canHitEpRight(false)
  {
    setNewPosition(*this, game, game.pawnPositions);
    
    if(mWhite)
      pathToImage = "img/wpawn.png";
    else
      pathToImage = "img/bpawn.png";
  }

  void qtc::pc::Pawn::movegen(const Board &game)
  {
    unsigned long long int hit{0};
    unsigned long long int onestep{0};
    unsigned long long int doublestep{0};
    const unsigned long long int allPositions =
      game.blackPositions | game.whitePositions;

    //std::bitset<64> pawnBits(allPositions);
    //std::cout << pawnBits;exit(1);
	  
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

    removeIllegalMoves(*this, game);
  }

  void qtc::pc::Pawn::move(Board &game, std::string desiredMove)
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

    const unsigned short int oldPosition = log2(mPosition);
    if( abs(numberMove-oldPosition) == 16)
    {
      if(game.pawnPositions & binaryField[numberMove+1])
	mpark::get<Pawn>(game.pieces.at(numberMove+1)).setCanHitEpLeft();
      if(game.pawnPositions & binaryField[numberMove-1])
        mpark::get<Pawn>(game.pieces.at(numberMove-1)).setCanHitEpRight();
    } 
    
    PromotionPiece promoteTo = none;
    const unsigned short int offboard = 64;
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
	game.createPiece<Queen >(offboard, mWhite);
	promoteTo =  queen;
	break;
    }
       
    deletePiece(*this, game, game.pawnPositions);

    removeEpPawn(game, numberMove);

    correctPiecePosition(*this, game, numberMove);
    
    mPosition = binaryMove;

    deletePieceFromHitPosition(*this, game);

    hasMoved = true;
    game.whiteToMove = !game.whiteToMove;

    if(promoteTo != none)
      promote(game, promoteTo);
    else
      setNewPosition(*this, game, game.pawnPositions);   
  }

  void qtc::pc::Pawn::promote(Board &game, const PromotionPiece promoteTo)
  {
    switch(promoteTo)
    {
      case knight:
	setNewPosition(*this, game, game.knightPositions); 
	break;
      case bishop:
	setNewPosition(*this, game, game.bishopPositions);
	break;
      case queen:
	setNewPosition(*this, game, game.queenPositions );
	break;
      case rook:
	setNewPosition(*this, game, game.rookPositions  );
	break;
      default:
	std::cerr << "could not promote!";
        return;
    }
	
    const unsigned short int position = log2(mPosition);
    const unsigned short int offboard = 64;
    const auto extractedPawn  = game.pieces.extract(position);
    auto pieceAfterPromotions = game.pieces.extract(offboard);
    
    pieceAfterPromotions.key() = position;
    game.pieces.insert(std::move(pieceAfterPromotions));

    if(mWhite)
      game.whitePositions |= mPosition;
    else
      game.blackPositions |= mPosition;
  }

  void qtc::pc::Pawn::removeEpPawn(Board &game, const unsigned short int numberMove)
  {
    const unsigned short int oldPosition = log2(mPosition);
    const unsigned long long int binaryMove = binaryField[numberMove];
    
    const unsigned long long int allPositions =
      game.blackPositions | game.whitePositions;
    
    if( abs(numberMove-oldPosition) == 7
	&& (allPositions | binaryMove) )
    {
      game.pieces.erase(numberMove-1);

      mPosition = numberMove-1;
      deletePieceFromHitPosition(*this, game);
    }
    if( abs(numberMove-oldPosition) == 9
        && (allPositions | binaryMove) )
    {
      game.pieces.erase(numberMove+1);
      
      mPosition = numberMove+1;
      deletePieceFromHitPosition(*this, game);
    }
    
    setPosition(oldPosition);
  }
