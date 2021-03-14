#include "board/board.h"
#include "pieces.h"

  short int qtc::Board::createPiecesFromFEN(std::string FENsection)
  {
    const bool black = false;
    const bool white = true;
    unsigned short int skip;
    unsigned short int position{0};
    unsigned short int whiteKingPosition{64};
    unsigned short int blackKingPosition{64};
    
    char help[1];
    for(const char character : FENsection)
    {
      if(isdigit(character))
      {
	help[0] = {character};
	skip = atoi(help);
	
	if(skip <= 1 && skip >= 8) return -1;

	position += skip;
      }
      switch(character)
      {
        case 'p':
	  createPiece<qtc::pc::Pawn  >(63-position,black);
	  break;
        case 'n':
	  createPiece<qtc::pc::Knight>(63-position,black);
	  break;
        case 'b':
	  createPiece<qtc::pc::Bishop>(63-position,black);
	  break;
        case 'r':
	  createPiece<qtc::pc::Rook  >(63-position,black);
	  break;
	case 'q':
	  createPiece<qtc::pc::Queen >(63-position,black);
	  break;
        case 'k':
	  createPiece<qtc::pc::King  >(63-position,black);
	  if(blackKingPosition != 64)
	    return -1;
	  blackKingPosition = position;
	  break;

        case 'P':
	  createPiece<qtc::pc::Pawn  >(63-position,white);
	  break;
        case 'N':
	  createPiece<qtc::pc::Knight>(63-position,white);
	  break;
        case 'B':
	  createPiece<qtc::pc::Bishop>(63-position,white);
	  break;
        case 'R':
	  createPiece<qtc::pc::Rook  >(63-position,white);
	  break;
	case 'Q':
	  createPiece<qtc::pc::Queen >(63-position,white);
	  break;
        case 'K':
	  createPiece<qtc::pc::King  >(63-position,white);
	  if(whiteKingPosition != 64)
	    return -1;
	  whiteKingPosition = position;
	  break;
	  
        case '/':
	  position--;
	  if(position%8 == 0) break;
	  else return -1;
        default:
	  return -1;

	++position;
      }
    }

    if(position != 63 ||
       !kingPositionsCorrect(whiteKingPosition, blackKingPosition))
      return -1;

    return 0;
  }

  short int qtc::Board::setMoveRightFromFEN(std::string FENsection)
  {
    const char character = FENsection[0];
    if     (character == 'w') whiteToMove = true;
    else if(character == 'b') whiteToMove = false;
    else return -1;

    return 0;
  }

  short int qtc::Board::setRochadeFromFEN(std::string FENsection)
  {
    whiteCanCastleShort = false;
    whiteCanCastleLong  = false;
    blackCanCastleShort = false;
    blackCanCastleLong  = false;

    for(const char character : FENsection)
    {
      if(character == '-')
      {
	if(FENsection.size() != 1) return -1;
	break;
      }
      switch(character)
      {
        case 'K':
	  whiteCanCastleShort = true;
	  break;
        case 'Q':
	  whiteCanCastleLong  = true;
          break;
        case 'k':
	  blackCanCastleShort = true;
          break;
        case 'q':
	  blackCanCastleLong  = true;
          break;
        default:
	  return -1;
      }
    }    

    return 0;
  }

  void qtc::Board::setEpFromFEN(std::string FENsection) const 
  {
    unsigned short int epPosition =
      getOriginFieldNumber(FENsection);
      
    if( whiteToMove && (epPosition <= 47 || epPosition >= 40))//row 7
    {
    if(pawnPositions & binaryField[epPosition+9])
      pieces.at(epPosition+9)->setCanHitEpLeft();
    if(pawnPositions & binaryField[epPosition+7])
      pieces.at(epPosition+7)->setCanHitEpRight();
    }
      
    if(!whiteToMove && (epPosition <= 23 || epPosition >= 16))//row 3
    {
      if(pawnPositions & binaryField[epPosition-7])
	pieces.at(epPosition-7)->setCanHitEpLeft();
      if(pawnPositions & binaryField[epPosition-9])
        pieces.at(epPosition-9)->setCanHitEpRight();
    }
  }

  std::string qtc::Board::computePiecesFEN() const 
  {
    std::string FENstring{};
    unsigned short int skip{0};
    unsigned short int piecesPerRow{0};
    for(unsigned short int binaryPosition = binaryField[a8];
	binaryPosition >= binaryField[h1];
	binaryPosition /= 2)
    {
      if (pawnPositions & binaryPosition)
      {
	if(skip)
	{
	  FENstring.append(std::to_string(skip));
	  skip = 0;
	}
	if (whitePositions & binaryPosition) FENstring.push_back('P');
	else FENstring.push_back('p');
	++piecesPerRow;
      }
      else if (knightPositions & binaryPosition)
      {
	if(skip)
	{
	  FENstring.append(std::to_string(skip));
	  skip = 0;
	}
	if (whitePositions & binaryPosition) FENstring.push_back('N');
	else FENstring.push_back('n');
	++piecesPerRow;
      }
      else if (bishopPositions & binaryPosition)
      {
	if(skip)
	{
	  FENstring.append(std::to_string(skip));
	  skip = 0;
	}
	if (whitePositions & binaryPosition) FENstring.push_back('B');
	else FENstring.push_back('b');
	++piecesPerRow;
      }
      else if (rookPositions & binaryPosition)
      {
	if(skip)
	{
	  FENstring.append(std::to_string(skip));
	  skip = 0;
	}
	if (whitePositions & binaryPosition) FENstring.push_back('R');
	else FENstring.push_back('r');
	++piecesPerRow;
      }
      else if (queenPositions & binaryPosition)
      {
	if(skip)
	{
	  FENstring.append(std::to_string(skip));
	  skip = 0;
	}
	if (whitePositions & binaryPosition) FENstring.push_back('Q');
	else FENstring.push_back('q');
	++piecesPerRow;
      }
      else if (kingPositions & binaryPosition)
      {
	if(skip)
	{
	  FENstring.append(std::to_string(skip));
	  skip = 0;
	}
	if (whitePositions & binaryPosition) FENstring.push_back('K');
	else FENstring.push_back('k');
	++piecesPerRow;
      }
      else ++skip;

      if(skip + piecesPerRow == 8)
      {
	FENstring.push_back('/');
	skip = 0;
	piecesPerRow = 0;
      }
    }

    return FENstring;
  }

  std::string qtc::Board::computeFENposition() const 
  {
    std::string FENstring = computePiecesFEN();
      
    FENstring.push_back(' ');

    if(whiteToMove) FENstring.push_back('w');
    else FENstring.push_back('b');

    FENstring.push_back(' ');

    if     (whiteCanCastleShort) FENstring.push_back('K');
    else if(whiteCanCastleLong)  FENstring.push_back('Q');
    else if(blackCanCastleShort) FENstring.push_back('k');
    else if(blackCanCastleLong)  FENstring.push_back('q');
    else FENstring.push_back('-');

    FENstring.push_back(' ');

    FENstring.append("a3");

    FENstring.push_back(' ');

    FENstring.append(std::to_string(movesSinceHit));
    
    FENstring.push_back(' ');

    FENstring.append(std::to_string(moveCounter + 1));

    const unsigned short int maxFENsize = 85;
    FENstring.resize(maxFENsize, ' ');

    return FENstring;
  }

  MPI_Request qtc::Board::sendFENtoNode(const int destination,
					const MPI_Comm communicator) const
  {
    const std::string FENstring = computeFENposition();
    
    const unsigned short int maxFENsize = 85;
    
    MPI_Request sendRequest;
      
    MPI_Ibsend(
      FENstring.c_str(),
      maxFENsize,
      MPI_BYTE,
      destination,
      0,
      communicator,
      &sendRequest);

    return sendRequest;
  }

std::string qtc::receiveFENfromNode(const int source,
				    const MPI_Comm communicator)
{
  MPI_Status status;
  int statusAmount;
   
  const unsigned short int maxFENsize = 85;
  const char *FENcarray = (char*)malloc(maxFENsize);
  MPI_Recv(
    (void*)FENcarray,
    maxFENsize,
    MPI_BYTE,
    source,
    0,
    communicator,
    &status);

  MPI_Get_count(&status, MPI_INT, &statusAmount);
  if(statusAmount) return "";

  const std::string FENstring{FENcarray};

  return FENstring;
}

void qtc::FENerror(const short int errorCode, const MPI_Comm communicator)
{
  if(errorCode) MPI_Abort(communicator, errorCode);
}
