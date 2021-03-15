#ifndef BOARD_H
#define BOARD_H

#include "mpi.h"
#include "stdlib.h"
#include "def.h"

#include "pieces.h"

namespace qtc {

unsigned long long int pow2(const unsigned short int);
std::vector<std::string> explode(std::string string,
				 const std::string delimiter = " ");
bool kingPositionsCorrect(const unsigned short int whiteKingPosition,
			  const unsigned short int blackKingPosition);
unsigned long long int computeThreatenedFields(std::vector<std::string> allMoves);
std::string receiveFENfromNode(const int source = 0,
			       const MPI_Comm communicator = MPI_COMM_WORLD);
void FENerror(const short int errorCode,
	      const MPI_Comm communicator = MPI_COMM_WORLD);
unsigned long long int computeThreatenedFields(std::vector<std::string> allMoves);

namespace pc {
class Pawn;
class Knight;
class Bishop;
class Queen;
class King;
class Rook;
};
//using Pieces = std::map<unsigned short int, std::shared_ptr<pc::Piece>>;
using Piece  = mpark::variant< pc::Pawn
			       ,pc::Knight
			       ,pc::Bishop
			       ,pc::Rook
			       ,pc::Queen
			       ,pc::King
			      >;
using Pieces = std::map<unsigned short int,
			Piece>;

class Board
{
 private:
  
  explicit Board()
  {
    const bool black = false;

    for(unsigned short int field = h7; field <= a7; field++)
      createPiece<pc::Pawn>(field, black);
    
    /*createPiece<pc::Rook  >(h8, black);
    createPiece<pc::Knight>(g8, black);
    createPiece<pc::Bishop>(f8, black);
    createPiece<pc::King  >(e8, black);
    createPiece<pc::Queen >(d8, black);
    createPiece<pc::Bishop>(c8, black);
    createPiece<pc::Knight>(b8, black);
    createPiece<pc::Rook  >(a8, black);
  
    //////////////////////////////////////////////////
    
    const bool white = true;
  
    for(unsigned short int field = h2; field <= a2; field++)
      createPiece<pc::Pawn>(field, white);
  
    createPiece<pc::Rook  >(h1, white);
    createPiece<pc::Knight>(g1, white);
    createPiece<pc::Bishop>(f1, white);
    createPiece<pc::King  >(e1, white);
    createPiece<pc::Queen >(d1, white);
    createPiece<pc::Bishop>(c1, white);
    createPiece<pc::Knight>(b1, white);
    createPiece<pc::Rook  >(a1, white);*/
  };

  explicit Board(std::string FENposition)
  {
    const std::vector<std::string> FENsections
      = explode(std::move(FENposition));
    if(FENsections.size() != 6) FENerror(-1);

    FENerror( createPiecesFromFEN(std::move(FENsections[0])) );
    
    FENerror( setMoveRightFromFEN(std::move(FENsections[1])) );
    
    FENerror( setRochadeFromFEN(  std::move(FENsections[2])) );

    setEpFromFEN(std::move(FENsections[3]));

    char character[] = {FENsections[4].at(0)};
    movesSinceHit = atoi(character);
    if(movesSinceHit >= 50) FENerror(-1);
    
    character[0] = {FENsections[5].at(0)};
    moveCounter  = atoi(character) - 1;
    halfMoveCounter = moveCounter*2;
    if(!whiteToMove) ++halfMoveCounter;

    if(whiteToMove)
    {
      threatenedFields = computeThreatenedFields(generateWhiteMoves());
      if(threatenedFields & kingPositions & blackPositions)
	FENerror(-1);
    }
    else
    {
      threatenedFields = computeThreatenedFields(generateBlackMoves());
      if(threatenedFields & kingPositions & blackPositions)
	FENerror(-1);
    }
  }

 public:
  
  static Board newgame()
  {
    Board game{};

    if(game.whiteToMove)
      game.threatenedFields = computeThreatenedFields(game.generateBlackMoves());
    else
      game.threatenedFields = computeThreatenedFields(game.generateWhiteMoves());

    return game;
  }
  
  static Board createBoardFromFEN(std::string FENposition)
  {
    Board game{std::move(FENposition)};
    
    if(game.whiteToMove)
      game.threatenedFields = computeThreatenedFields(game.generateBlackMoves());
    else
      game.threatenedFields = computeThreatenedFields(game.generateWhiteMoves());

    return game;
  }

  static Board createBoardFromNode(const int source = 0,
				   const MPI_Comm communicator = MPI_COMM_WORLD)
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
  
  std::vector<std::string> generateWhiteMoves();
  std::vector<std::string> generateBlackMoves();
  
  std::vector<std::string> update();
  
  short int createPiecesFromFEN(std::string FENsection);
  short int setMoveRightFromFEN(std::string FENsection);
  short int   setRochadeFromFEN(std::string FENsection);
  void             setEpFromFEN(std::string FENsection) const;
  std::string computePiecesFEN() const ;
  std::string computeFENposition() const;
  MPI_Request sendFENtoNode(const int destination,
			    const MPI_Comm communicator = MPI_COMM_WORLD) const;
  
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

unsigned short int getOriginFieldNumber(std::string move);
unsigned long long int convertStringToBinaryPosition(std::string move);
unsigned short int convertStringToPosition(std::string move);
void move(Board &game, std::string desiredMove);
bool isMate(Board &game);
bool isStalemate(Board &game);

unsigned short int playRandom(Board game);
float computeWinProbability(const Board &game, const unsigned long long int numberOfGames);

};

#endif
