#ifndef BOARD_H
#define BOARD_H

#include "mpi.h"
#include "stdlib.h"
#include "def.h"

unsigned long long int pow2(unsigned short int);
std::vector<std::string> explode(std::string string,
				 const std::string delimiter = " ");
bool kingPositionsCorrect(unsigned short int whiteKingPosition,
			  unsigned short int blackKingPosition);
std::string receiveFENfromNode(int source = 0,
			       MPI_Comm communicator = MPI_COMM_WORLD);
void FENerror(short int errorCode,
	      MPI_Comm communicator = MPI_COMM_WORLD);


class Piece;
using Pieces = std::map<unsigned short int, std::shared_ptr<Piece>>;
//using Piece = mpark::variant<Pawn,Knight,Bishop,Rook,Queen>;
//using Pieces = std::map<unsigned short int, Piece>;
class Pawn;
class Knight;
class Bishop;
class Queen;
class King;
class Rook;

class Board
{
 private:
  
  explicit Board()
  {
    bool black = false;

    for(unsigned short int field = h7; field <= a7; field++)
      createPiece<Pawn>(field, black);
    
    createPiece<Rook  >(h8, black);
    createPiece<Knight>(g8, black);
    createPiece<Bishop>(f8, black);
    createPiece<King  >(e8, black);
    createPiece<Queen >(d8, black);
    createPiece<Bishop>(c8, black);
    createPiece<Knight>(b8, black);
    createPiece<Rook  >(a8, black);
  
    //////////////////////////////////////////////////
    
    bool white = true;
  
    for(unsigned short int field = h2; field <= a2; field++)
      createPiece<Pawn>(field, white);
  
    createPiece<Rook  >(h1, white);
    createPiece<Knight>(g1, white);
    createPiece<Bishop>(f1, white);
    createPiece<King  >(e1, white);
    createPiece<Queen >(d1, white);
    createPiece<Bishop>(c1, white);
    createPiece<Knight>(b1, white);
    createPiece<Rook  >(a1, white);
  };

  explicit Board(std::string FENposition)
  {
    std::vector<std::string> FENsections
      = explode(std::move(FENposition));
    if(FENsections.size() != 6) FENerror(-1);

    FENerror( createPiecesFromFEN(std::move(FENsections[0])) );
    
    FENerror( setMoveRightFromFEN(std::move(FENsections[1])) );
    
    FENerror( setRochadeFromFEN(  std::move(FENsections[2])) );

    setEpFromFEN(std::move(FENsections[3]));

    char character[] = {FENsections[4].at(0)};
    movesSinceHit = atoi(character);
    if(movesSinceHit >= 50) exit(0);
    
    character[0] = {FENsections[5].at(0)};
    moveCounter  = atoi(character) - 1;
    halfMoveCounter = moveCounter*2;
    if(!whiteToMove) ++halfMoveCounter;

    if(whiteToMove)
    {
      threatenedFields = generateWhiteMoves();
      if(threatenedFields & kingPositions & blackPositions)
	FENerror(-1);
    }
    else
    {
      threatenedFields = generateBlackMoves();
      if(threatenedFields & kingPositions & blackPositions)
	FENerror(-1);
    }
  }

 public:
  
  static Board newgame()
  {
    Board game{};

    if(game.whiteToMove)
      game.threatenedFields = game.generateBlackMoves();
    else
      game.threatenedFields = game.generateWhiteMoves();

    return game;
  }
  
  static Board createBoardFromFEN(std::string FENposition)
  {
    Board game{std::move(FENposition)};
    
    if(game.whiteToMove)
      game.threatenedFields = game.generateBlackMoves();
    else
      game.threatenedFields = game.generateWhiteMoves();

    return game;
  }

  static Board createBoardFromNode(int source = 0,
				   MPI_Comm communicator = MPI_COMM_WORLD)
  { 
    return createBoardFromFEN(
     receiveFENfromNode(source, communicator)
    );
  }
  
  template<typename T>
  void createPiece(unsigned short int position, bool isWhite);
  
  bool operator==(const Board &rhs) const;
  
  void printPositionsBinary() const;
  bool positionsMatchWithPieces() const;
  
  unsigned long long int generateWhiteMoves();
  unsigned long long int generateBlackMoves();
  unsigned long long int computeThreatenedFields();
  
  void update();
  
  short int createPiecesFromFEN(std::string FENsection);
  short int setMoveRightFromFEN(std::string FENsection);
  short int   setRochadeFromFEN(std::string FENsection);
  void             setEpFromFEN(std::string FENsection);
  std::string computePiecesFEN();
  std::string computeFENposition();
  MPI_Request sendFENtoNode(int destination,
			    MPI_Comm communicator = MPI_COMM_WORLD);

  bool whiteToMove{true};

  bool whiteCanCastleShort{true};
  bool whiteCanCastleLong{true};
  bool blackCanCastleShort{true};
  bool blackCanCastleLong{true};

  bool whiteIsChecked{false};
  bool whiteIsCheckmate{false};
  bool whiteIsStalemate{false};
  bool blackIsChecked{false};
  bool blackIsCheckmate{false};
  bool blackIsStalemate{false};

  unsigned short int moveCounter{0};
  unsigned short int halfMoveCounter{0};
  unsigned short int movesSinceHit{0};
  
  unsigned long long int   pawnPositions{0};
  unsigned long long int knightPositions{0};  
  unsigned long long int bishopPositions{0};  
  unsigned long long int   rookPositions{0};  
  unsigned long long int  queenPositions{0};  
  unsigned long long int   kingPositions{0};
  unsigned long long int  whitePositions{0}; 
  unsigned long long int  blackPositions{0};
  
  unsigned long long int threatenedFields{0}; 

  Pieces pieces{};
};

unsigned short int getOriginFieldNumber(std::string &move);
unsigned long long int convertStringToBinaryPosition(std::string &move);
unsigned short int convertStringToPosition(std::string &move);
void move(Board &game, std::string &desiredMove);
bool isMate(Board &game);
bool isStalemate(Board &game);

#endif
