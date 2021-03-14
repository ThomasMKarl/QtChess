#include "board/board.h"
#include "pieces.h"

unsigned long long int qtc::computeThreatenedFields(std::vector<std::string> allMoves)
{
  unsigned long long int binaryMoves = 0;
  for(auto &move : allMoves)
    binaryMoves |= convertStringToBinaryPosition(move);

  return binaryMoves;
}

unsigned short int qtc::getOriginFieldNumber(std::string move)
{
  if(move.length() < 4)
  {
    std::cerr << "invalid move!\n";
    return 0;
  }

  const unsigned short int number = convertStringToPosition(move);
  move.erase(move.begin(), move.begin()+2);
    
  return number;
}

unsigned long long int qtc::convertStringToBinaryPosition(std::string move)
{ 
  return binaryField[ convertStringToPosition(move) ];
}

unsigned short int qtc::convertStringToPosition(std::string move)
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

  const short int row = (int)(move[1]) - 48;
  if(row > 8 || row < 1)
  {
    std::cerr << "impossible move!\n";
    return 0;
  }
    
  return 8*(row-1)+line-1;
}

void qtc::move(Board &game, std::string desiredMove)
{
  const unsigned short int from = getOriginFieldNumber(desiredMove);
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
  
  game.pieces[from]->move(game,desiredMove);
  //Move move{game};
  //move.setDesiredMove(desiredMove);
  //mpark::visit(move, game.pieces.at(from));

  ++game.halfMoveCounter;
  game.moveCounter = ceil(game.halfMoveCounter/2.0f);
}

bool qtc::isMate(Board &game)
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

bool qtc::isStalemate(Board &game)
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

unsigned long long int qtc::pow2(const unsigned short int value)
{
  return 1ULL << value;
}

std::vector<std::string> qtc::explode(std::string string,
				      const std::string delimiter)
{
  std::vector<std::string> result{};

  const unsigned short int stringLength = string.length();
  const unsigned short int delimiterLength = delimiter.length();
  if(!delimiterLength)
  {
    result.push_back(string);
    return result;
  }

  unsigned short int outerIterator{0};
  unsigned short int innerIterator{0};
  unsigned short int delimiterIterator{0};
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

bool qtc::kingPositionsCorrect(unsigned short int whiteKingPosition,
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

unsigned short int qtc::playRandom(Board game)
{
  const bool engineColorIsWhite = game.whiteToMove;

  std::vector<std::string> possibleMoves{};
  
  while(true)
  {   
    possibleMoves = game.update();
    
    if(isStalemate(game)) return 1;
    if(isMate(game))
    {
      if(game.whiteToMove)
      {
	if(engineColorIsWhite) return 0;
	else                   return 2;
      }
      else
      {
	if(engineColorIsWhite) return 2;
        else                   return 0;
      }
    }
    
    std::default_random_engine generator;
    std::uniform_int_distribution<unsigned short int> distribution(0,possibleMoves.size());
    move(game, possibleMoves[distribution(generator)]);
  }
}

float qtc::computeWinProbability(const Board &game, const unsigned long long int numberOfGames)
{
  unsigned long long int wins = 0;
  unsigned long long int partialWins = 0;
  #pragma omp parallel private(partialWins)
  {
    #pragma omp for
    for(unsigned long long int i = 0; i < numberOfGames; ++i)
      partialWins += playRandom(game);
  }
   
  #pragma omp parallel reduction(+:wins)
  wins += partialWins;
  
  return wins/(2.0*numberOfGames);
}
