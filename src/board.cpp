#include "board.h"
#include "pieces.h"

  template<typename T>
  void Board::createPiece(unsigned short int position, bool isWhite)
  {
    pieces.insert({position, std::make_shared<T>(*this,position,isWhite)});
    //pieces.insert({position, T{*this,position,isWhite}});
  }
  template void Board::createPiece<Pawn>
    (unsigned short int position, bool isWhite);
  template void Board::createPiece<Knight>
    (unsigned short int position, bool isWhite);
  template void Board::createPiece<Bishop>
    (unsigned short int position, bool isWhite);
  template void Board::createPiece<Rook>
    (unsigned short int position, bool isWhite);
  template void Board::createPiece<Queen>
    (unsigned short int position, bool isWhite);
  template void Board::createPiece<King>
    (unsigned short int position, bool isWhite);

  bool Board::operator==(const Board &rhs) const
  {
    if(pawnPositions   != rhs.pawnPositions)   return false;
    if(knightPositions != rhs.knightPositions) return false;
    if(bishopPositions != rhs.bishopPositions) return false;
    if(rookPositions   != rhs.rookPositions)   return false;
    if(queenPositions  != rhs.queenPositions)  return false;
    if(kingPositions   != rhs.kingPositions)   return false;
    if(whitePositions  != rhs.whitePositions)  return false;
    if(blackPositions  != rhs.blackPositions)  return false;

    if(whiteToMove     != rhs.whiteToMove) return false;

    if(whiteCanCastleShort != rhs.whiteCanCastleShort) return false;
    if(whiteCanCastleLong  != rhs.whiteCanCastleLong)  return false;
    if(blackCanCastleShort != rhs.blackCanCastleShort) return false;
    if(blackCanCastleLong  != rhs.blackCanCastleLong)  return false;

    if(whiteIsChecked   != rhs.whiteIsChecked)   return false;
    if(whiteIsCheckmate != rhs.whiteIsCheckmate) return false;
    if(whiteIsStalemate != rhs.whiteIsStalemate) return false;
    if(blackIsChecked   != rhs.blackIsChecked)   return false;
    if(blackIsCheckmate != rhs.blackIsCheckmate) return false;
    if(blackIsStalemate != rhs.blackIsStalemate) return false;
       
    return true;
  }

  void Board::printPositionsBinary() const
  {
    std::cout <<
      "         ----------------------------------------------------------------\n";
    std::cout <<
      "         abcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefghabcdefgh\n";
    std::cout <<
      "         |  8   ||  7   ||  6   ||  5   ||  4   ||  3   ||  2   ||  1   |\n";
    std::cout <<
      "         ----------------------------------------------------------------\n";
      
    std::bitset<64> pawnBits(pawnPositions);
    std::cout << "Pawns:   "     << pawnBits;

    std::bitset<64> knightBits(knightPositions);
    std::cout << "\nKnights: "   << knightBits;
    
    std::bitset<64> bishopBits(bishopPositions);
    std::cout << "\nBishops: "   << bishopBits;
    
    std::bitset<64> rookBits(rookPositions);
    std::cout << "\nRooks:   "   << rookBits;
    
    std::bitset<64> queenBits(queenPositions);
    std::cout << "\nQueens:  "   << queenBits;
    
    std::bitset<64> kingBits(kingPositions);
    std::cout << "\nKings:   "   << kingBits;
    
    std::bitset<64> whiteBits(whitePositions);
    std::cout << "\n\nWhite:   " << whiteBits;
    
    std::bitset<64> blackBits(blackPositions);
    std::cout << "\nBlack:   "   << blackBits << '\n';
  }

  bool Board::positionsMatchWithPieces() const
  {
    for(const auto& [position, piece] : pieces)
    {
      if(piece->getPosition() != position)
      {
        std::cerr << "Positions mismatch at position " << position
		  << ". Piece has position " << piece->getPosition() << '\n';
	return false;
      }
    }

    return true;
  }

  unsigned long long int Board::generateWhiteMoves()
  {
    unsigned long long int whiteMoves = 0;
    for(const auto& [position, piece] : pieces)
    {
      if(piece->isWhite())
      {
	piece->movegen(*this);
	whiteMoves |= piece->getPossibleMoves();
      }
    }

    return whiteMoves;
  }

  unsigned long long int Board::generateBlackMoves()
  {
    unsigned long long int blackMoves = 0;
    for(const auto& [position, piece] : pieces)
    {
      if(!piece->isWhite())
      {
	piece->movegen(*this);
	blackMoves |= piece->getPossibleMoves();
      }
    }

    return blackMoves;
  }

  void Board::update()
  {
    unsigned long long int possibleMoves;
    
    if(whiteToMove)
    {     
      if(threatenedFields & kingPositions & whitePositions)
	whiteIsChecked = false;
      else
	whiteIsChecked = true;
      
      possibleMoves = generateWhiteMoves();

      if(!possibleMoves)
      {
	whiteIsStalemate = true;
	if(whiteIsChecked)
	{
	  whiteIsStalemate = false;
	  whiteIsCheckmate = true;
	}
      }
    }
    else
    {   
      if(threatenedFields & kingPositions & blackPositions)
	blackIsChecked = false;
      else
	blackIsChecked = true;
      
      possibleMoves = generateBlackMoves();

      if(!possibleMoves)
      {
	blackIsStalemate = true;
	if(whiteIsChecked)
	{
	  blackIsStalemate = false;
	  blackIsCheckmate = true;
	}
      }
    }

    threatenedFields = possibleMoves;
  }

  short int Board::createPiecesFromFEN(std::string FENsection)
  {
    bool black = false;
    bool white = true;
    unsigned short int skip;
    unsigned short int position{0};
    unsigned short int whiteKingPosition{64};
    unsigned short int blackKingPosition{64};
    
    char help[1];
    for(char character : FENsection)
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
	  createPiece<Pawn>(63-position,black);
	  break;
        case 'n':
	  createPiece<Pawn>(63-position,black);
	  break;
        case 'b':
	  createPiece<Pawn>(63-position,black);
	  break;
        case 'r':
	  createPiece<Pawn>(63-position,black);
	  break;
	case 'q':
	  createPiece<Pawn>(63-position,black);
	  break;
        case 'k':
	  createPiece<Pawn>(63-position,black);
	  if(blackKingPosition != 64)
	    return -1;
	  blackKingPosition = position;
	  break;

        case 'P':
	  createPiece<Pawn>(63-position,white);
	  break;
        case 'N':
	  createPiece<Pawn>(63-position,white);
	  break;
        case 'B':
	  createPiece<Pawn>(63-position,white);
	  break;
        case 'R':
	  createPiece<Pawn>(63-position,white);
	  break;
	case 'Q':
	  createPiece<Pawn>(63-position,white);
	  break;
        case 'K':
	  createPiece<Pawn>(63-position,white);
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

  short int Board::setMoveRightFromFEN(std::string FENsection)
  {
    char character = FENsection[0];
    if     (character == 'w') whiteToMove = true;
    else if(character == 'b') whiteToMove = false;
    else return -1;

    return 0;
  }

  short int Board::setRochadeFromFEN(std::string FENsection)
  {
    whiteCanCastleShort = false;
    whiteCanCastleLong  = false;
    blackCanCastleShort = false;
    blackCanCastleLong  = false;

    for(char character : FENsection)
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

  void Board::setEpFromFEN(std::string FENsection)
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

  std::string Board::computePiecesFEN()
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

  std::string Board::computeFENposition()
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

    unsigned short int maxFENsize = 85;
    FENstring.resize(maxFENsize, ' ');

    return FENstring;
  }

  MPI_Request Board::sendFENtoNode(int destination, MPI_Comm communicator)
  {
    std::string FENstring = computeFENposition();
    
    unsigned short int maxFENsize = 85;
    
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

  //////////////////////////////////////////////////////////////////

  unsigned short int getOriginFieldNumber(std::string &move)
  {
    if(move.length() < 4)
    {
      std::cerr << "invalid move!\n";
      return 0;
    }

    unsigned short int number = convertStringToPosition(move);
    move.erase(move.begin(), move.begin()+2);
    
    return number;
  }

  unsigned long long int convertStringToBinaryPosition(std::string &move)
  { 
    return binaryField[ convertStringToPosition(move) ];
  }

  unsigned short int convertStringToPosition(std::string &move)
  {
    if(move.length() < 2)
    {
      std::cerr << "impossible move!\n";
      return 0;
    }
    
    short int line;
    switch(move[0])
    {
      case 'a':
	line = 8;
	break;
      case 'b':
	line = 7;
	break;
      case 'c':
	line = 6;
	break;
      case 'd':
	line = 5;
	break;
      case 'e':
	line = 4;
	break;
      case 'f':
	line = 3;
	break;
      case 'g':
	line = 2;
	break;
      case 'h':
	line = 1;
	break;
      default:
	std::cerr << "impossible move!\n";
	return 0;
    }

    short int row = (int)(move[1]) - 48;
    if(row > 8 || row < 1)
    {
      std::cerr << "impossible move!\n";
      return 0;
    }
    
    return 8*(row-1)+line-1;
  }

void move(Board &game, std::string &desiredMove)
{
  unsigned short int from = getOriginFieldNumber(desiredMove);
  if(!from) return;

  unsigned long long int sameColorPositions;
  if(game.whiteToMove)
    sameColorPositions = game.whitePositions;
  else
    sameColorPositions = game.blackPositions;
  
  if(!(binaryField[from] & sameColorPositions))
  {
    std::cerr << "impossible move!\n";
    return;
  }
  
  game.pieces.at(from)->move(game,desiredMove);
  //mpark::visit(Move{game,desiredMove}, game.pieces.at(from));

  ++game.halfMoveCounter;
  game.moveCounter = ceil(game.halfMoveCounter/2.0f);
}

bool isMate(Board &game)
{
  if(game.whiteIsCheckmate)
  {
    std::cout << "Black has won!\n";
    return true;
  }
  if(game.blackIsCheckmate)
  {
    std::cout << "White has won!\n";
    return true;
  }

  return false;
}

bool isStalemate(Board &game)
{
  if(game.whiteIsStalemate)
  {
    std::cout << "Black has won!\n";
    return true;
  }
  if(game.blackIsStalemate)
  {
    std::cout << "White has won!\n";
    return true;
  }

  return false;
}

unsigned long long int pow2(unsigned short int value)
{
  return 1ULL << value;
}

std::vector<std::string> explode(std::string string,
				 const std::string delimiter)
{
  std::vector<std::string> result{};

  unsigned short int stringLength = string.length();
  int delimiterLength = delimiter.length();
  if(!delimiterLength)
  {
    result.push_back(string);
    return result;
  }

  int outerIterator{0};
  int innerIterator{0};
  int delimiterIterator{0};
  while(outerIterator < stringLength)
  {
      delimiterIterator = 0;
	
      while(outerIterator + delimiterIterator
              < stringLength &&
            delimiterIterator
              < delimiterLength &&
            string[outerIterator+delimiterIterator]
              == delimiter[delimiterIterator])
        ++delimiterIterator;
	
      if(delimiterIterator == delimiterLength)
      {
          result.push_back(
            string.substr(innerIterator, outerIterator-innerIterator)
          );
          outerIterator += delimiterLength;
          innerIterator = outerIterator;
      }
      else ++outerIterator;
  }
    
  result.push_back(
    string.substr(innerIterator, outerIterator-innerIterator)
  );
    
  return result;
}

bool kingPositionsCorrect(unsigned short int whiteKingPosition,
			  unsigned short int blackKingPosition)
{
  if(whiteKingPosition == 64 || blackKingPosition == 64)
    return false;

  unsigned short int kingsDistance =
    abs(whiteKingPosition - blackKingPosition);
  if(kingsDistance == 1 ||
     kingsDistance == 7 ||
     kingsDistance == 8 ||
     kingsDistance == 9)
    return false;
  else return true;
}

std::string receiveFENfromNode(int source, MPI_Comm communicator)
{
  MPI_Status status;
  int statusAmount;
   
  unsigned short int maxFENsize = 85;
  char *FENcarray = (char*)malloc(maxFENsize);
  MPI_Recv(
    FENcarray,
    maxFENsize,
    MPI_BYTE,
    source,
    0,
    communicator,
    &status);

  MPI_Get_count(&status, MPI_INT, &statusAmount);
  if(statusAmount) return "";

  std::string FENstring{FENcarray};

  return FENstring;
}

void FENerror(short int errorCode, MPI_Comm communicator)
{
  if(errorCode) MPI_Abort(communicator, errorCode);
}
