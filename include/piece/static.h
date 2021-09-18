#ifndef PIECE_H
#define PIECE_H

namespace qtc {

struct MoveGenerator
{
  MoveGenerator(const Board& board) {boardResource = std::make_shared<Board>(board);}

  template<typename T>
  void operator()(T& piece)
  {
    const Board board = *boardResource.get();
    piece.movegen(board);
    possibleMoves = computePossibleMoves(piece);
  }

  std::vector<std::string> getPossibleMoves() const {return possibleMoves;} 
  
 private:
  std::shared_ptr<Board> boardResource{};
  std::vector<std::string> possibleMoves{};
};

struct Move
{
  Move(const Board& board) {boardResource = std::make_shared<Board>(board);}

  void setDesiredMove(std::string move) {move_ = move;}
  
  template<typename T>
  void operator()(T& piece) const {piece.move(*boardResource.get(), move_);}

 private:
  std::shared_ptr<Board> boardResource{};
  std::string move_{};
};
  
struct EPsetter
{
  EPsetter(bool left_) : left(left_) {}
  
  template<typename T>
  void operator()(T& piece) const {auto help = piece;}
  void operator()(qtc::pc::Pawn& pawn) const
  {
    if(left)
      pawn.setCanHitEpLeft();
    else
      pawn.setCanHitEpRight();
  }
  
 private:
  bool left{};
};

namespace pc {

  template <typename T>
  std::vector<std::string> computePossibleMoves(const T& piece)
  {
    const std::bitset<sizeof(unsigned long long int) * CHAR_BIT>
      bit(piece.getPossibleMoves());
    
    std::vector<std::string> moves{};
    for(unsigned short int b = 0; b < 64; b++)
    {
      if(bit[b] == 1)
	moves.push_back( fieldMap[log2(piece.getPosition())] + fieldMap[b] );
    }

    return moves;
  }
  
  template <typename T>
  bool isImpossible(const T& piece, const unsigned long long int move)
  {
    return !(move & piece.getPossibleMoves());
  }

  template <typename T>
  void setNewPosition(const T& piece, Board &game, unsigned long long int &positions)
  {
    unsigned long long int newPosition = binaryField[piece.getPosition()];
    positions |= newPosition;
    
    if(piece.isWhite())
      game.whitePositions |= newPosition;
    else
      game.blackPositions |= newPosition;
  }
  
  template <typename T>
  void deletePiece(const T& piece, Board &game, unsigned long long int &positions)
  {
    unsigned long long int oldPosition = binaryField[piece.getPosition()];
    positions &= ~oldPosition;
    
    if(piece.isWhite())
      game.whitePositions &= ~oldPosition;
    else
      game.blackPositions &= ~oldPosition;
  }
  
  template <typename T>
  void deletePieceFromHitPosition(const T& piece, Board &game)
  {
    unsigned long long int oldPosition = binaryField[piece.getPosition()];
    game.pawnPositions   &= ~oldPosition;
    game.knightPositions &= ~oldPosition;
    game.bishopPositions &= ~oldPosition;
    game.rookPositions   &= ~oldPosition;
    game.queenPositions  &= ~oldPosition;
    
    game.whitePositions  &= ~oldPosition;
    game.blackPositions  &= ~oldPosition;
  }
  
  template <typename T>
  bool shiftMovesBlocked(T& piece, const Board &game, const unsigned long long int shift)
  {
    if( piece.isWhite() && (shift & game.whitePositions) != 0)
      return true;
      
    if( piece.isWhite() && (shift & game.blackPositions) != 0)
    {
      piece.setPossibleMoves( piece.getPossibleMoves() | shift );
      return true;
    }

    if(!piece.isWhite() && (shift & game.blackPositions) != 0)
      return true;
      
    if(!piece.isWhite() && (shift & game.whitePositions) != 0)
    {
      piece.setPossibleMoves( piece.getPossibleMoves() | shift );
      return true;
    }
    
    piece.setPossibleMoves( piece.getPossibleMoves() | shift );
    return false;
  }
  
  template <typename T>
  void correctPiecePosition(const T& piece, Board &game, const unsigned short int newPosition)
  {
    const short int oldPosition = piece.getPosition();
    
    game.pieces.erase(newPosition);
    
    auto extractedPiece = game.pieces.extract(oldPosition);
    extractedPiece.key() = newPosition;
    game.pieces.insert(std::move(extractedPiece));
  }
  
  template <typename T>
  void removeIllegalMoves(T& piece, const Board &game)
  {
    std::bitset<sizeof(unsigned long long int) * CHAR_BIT>
      bit(piece.getPossibleMoves());
    const short int oldPosition = piece.getPosition();
    
    unsigned long long int threatenedFields;

    Move move{game};

    for(unsigned short int b = 0; b < 64; b++)
    {
      if(bit[b] == 1)
      {
	Board gameCopy = game;

	move.setDesiredMove(fieldMap[b]);
	mpark::visit(move, gameCopy.pieces.at( oldPosition ));
        if(piece.isWhite())
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

    piece.setPossibleMoves(bit.to_ullong());
  }

};};

#endif
