#include "qtchess.h"

using namespace qtc;

int main(int argc, char* argv[])
{
  if(argc > 2) std::cerr << "Usage: " << argv[0] << " \"<FEN String>\"\n";

  if(argc = 2) Board board = Board::createBoardFromFEN(argv[1]);
  else         Board board = Board::newgame();
  
  while(true)
  {/*
    std::cout << "         ## Position after "
	      << board.moveCounter << " moves ##\n";
    
    board.printPositionsBinary();
    
    board.update();
    if(isMate(board))      break;
    if(isStalemate(board)) break;
    
    std::cout << "\n";

    std::string desiredMove;
    if(board.whiteToMove) std::cout << "White move: ";
    else                  std::cout << "Black move: ";
    std::getline(std::cin, desiredMove);
    std::cout << '>' << desiredMove << " \n\n";
    
    if(desiredMove[0] == 'q')
    {
      std::cout << "Aborted by user.\n";
      break;
    }
    
    if(desiredMove == "")
    {
      board.whiteToMove = !board.whiteToMove;
      std::cout << "Inserted zero move.\n";
    }
    else
    {
      move(board,desiredMove);
    }*/
  }
  
  return EXIT_SUCCESS;
}
