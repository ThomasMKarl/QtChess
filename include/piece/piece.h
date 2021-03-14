#ifndef PIECE_H
#define PIECE_H

#include "board/board.h"


namespace qtc {

struct MoveGenerator
{
  MoveGenerator(const Board& board) {boardResource = std::make_shared<Board>(board);}

  template<typename T>
  void operator()(const T& piece) const {piece.movegen();}

 private:
  std::shared_ptr<Board> boardResource{};
};

struct Move
{
  Move(const Board& board) {boardResource = std::make_shared<Board>(board);}

  void setDesiredMove(std::string move) {move_ = move;}
  
  template<typename T>
  void operator()(const T& piece) const {piece.move(move_);}

 private:
  std::shared_ptr<Board> boardResource{};
  std::string move_{};
};


namespace pc {
    
class Piece
{
 public:
  explicit Piece(const unsigned short int position, const bool isWhite)
    : mPosition(1ULL << position), mWhite(isWhite) {};
  
  virtual ~Piece(){};
  virtual void movegen(const Board&) {};
  virtual void move(Board&, std::string) {};
  
  unsigned short int getPosition() const {return log2(mPosition);}
  void setPosition(const unsigned short int position) {mPosition = pow2(position);}
  unsigned long long int getPossibleMoves() const {return mPossibleMoves;}
  bool isWhite() const {return mWhite;}
  virtual void setCanHitEpLeft()  {};
  virtual void setCanHitEpRight() {};
  
  std::vector<std::string> computePossibleMoves() const
  {
    const std::bitset<sizeof(unsigned long long int) * CHAR_BIT>
      bit(mPossibleMoves);
    
    std::vector<std::string> moves{};
    for(unsigned short int b = 0; b < 64; b++)
    {
      if(bit[b] == 1)
	moves.push_back( fieldMap[log2(mPosition)] + fieldMap[b] );
    }

    return moves;
  }
  
  bool isImpossible(const unsigned long long int move)
  {
    return !(move & mPossibleMoves);
  }

  std::string pathToImage{};

 protected:
  unsigned long long int mPosition{0};
  unsigned long long int mPossibleMoves{0};
  bool mWhite{true};

  void setNewPosition(Board &game, unsigned long long int &positions)
  {
    positions |= mPosition;
    
    if(mWhite)
      game.whitePositions |= mPosition;
    else
      game.blackPositions |= mPosition;
  }

  void deletePiece(Board &game, unsigned long long int &positions)
  {
    positions &= ~mPosition;
    
    if(mWhite)
      game.whitePositions &= ~mPosition;
    else
      game.blackPositions &= ~mPosition;
  }

  void deletePieceFromHitPosition(Board &game)
  {
    game.pawnPositions   &= ~mPosition;
    game.knightPositions &= ~mPosition;
    game.bishopPositions &= ~mPosition;
    game.rookPositions   &= ~mPosition;
    game.queenPositions  &= ~mPosition;
    
    game.whitePositions  &= ~mPosition;
    game.blackPositions  &= ~mPosition;
  }

  bool shiftMovesBlocked(const Board &game, const unsigned long long int shift)
  {
    if( mWhite && (shift & game.whitePositions) != 0)
      return true;
      
    if( mWhite && (shift & game.blackPositions) != 0)
    {
      mPossibleMoves |= shift;
      return true;
    }

    if(!mWhite && (shift & game.blackPositions) != 0)
      return true;
      
    if(!mWhite && (shift & game.whitePositions) != 0)
    {
      mPossibleMoves |= shift;
      return true;
    }
    
    mPossibleMoves |= shift;
    return false;
  }

  void correctPiecePosition(Board &game, const unsigned short int newPosition)
  {
    const short int oldPosition = log2(mPosition);
    
    game.pieces.erase(newPosition);
    
    auto extractedPiece = game.pieces.extract(oldPosition);
    extractedPiece.key() = newPosition;
    game.pieces.insert(std::move(extractedPiece));
  }

  void removeIllegalMoves(const Board &game)
  {
    std::bitset<sizeof(unsigned long long int) * CHAR_BIT> bit(mPossibleMoves);
    unsigned long long int threatenedFields;

    //Move move{game};

    for(unsigned short int b = 0; b < 64; b++)
    {
      if(bit[b] == 1)
      {
	Board gameCopy = game;
        gameCopy.pieces.at( log2(mPosition) ) ->move( gameCopy,fieldMap[b] );
	//move.setDesiredMove(fieldMap[b]);
	//mpark::visit(move, gameCopy.pieces.at( log2(mPosition) ));
        if(mWhite)
	{
	  threatenedFields =
	    computeThreatenedFields(gameCopy.generateBlackMoves());
	  if(threatenedFields &
	     gameCopy.kingPositions &
	     gameCopy.whitePositions)
	    bit.reset(b);
	}
        else
	{
	  threatenedFields =
	    computeThreatenedFields(gameCopy.generateWhiteMoves());
	  if(threatenedFields &
	     gameCopy.kingPositions &
	     gameCopy.blackPositions)
	    bit.reset(b);
	}
      }
    }

    mPossibleMoves = bit.to_ullong();
  }
};

};};

#endif
