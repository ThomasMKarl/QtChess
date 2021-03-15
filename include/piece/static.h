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
    positions |= piece.getPosition();
    
    if(piece.isWhite())
      game.whitePositions |= piece.getPosition();
    else
      game.blackPositions |= piece.getPosition();
  }
  
  template <typename T>
  void deletePiece(const T& piece, Board &game, unsigned long long int &positions)
  {
    positions &= ~piece.getPosition();
    
    if(piece.isWhite())
      game.whitePositions &= ~piece.getPosition();
    else
      game.blackPositions &= ~piece.getPosition();
  }
  
  template <typename T>
  void deletePieceFromHitPosition(const T& piece, Board &game)
  {
    game.pawnPositions   &= ~piece.getPosition();
    game.knightPositions &= ~piece.getPosition();
    game.bishopPositions &= ~piece.getPosition();
    game.rookPositions   &= ~piece.getPosition();
    game.queenPositions  &= ~piece.getPosition();
    
    game.whitePositions  &= ~piece.getPosition();
    game.blackPositions  &= ~piece.getPosition();
  }
  
  template <typename T>
  bool shiftMovesBlocked(const T& piece, const Board &game, const unsigned long long int shift)
  {
    if( piece.isWhite() && (shift & game.whitePositions) != 0)
      return true;
      
    if( piece.isWhite() && (shift & game.blackPositions) != 0)
    {
      piece.setPosition( piece.getPossibleMoves() | shift );
      return true;
    }

    if(!piece.isWhite() && (shift & game.blackPositions) != 0)
      return true;
      
    if(!piece.isWhite() && (shift & game.whitePositions) != 0)
    {
      piece.setPosition( piece.getPossibleMoves() | shift );
      return true;
    }
    
    piece.setPosition( piece.getPossibleMoves() | shift );
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
        //gameCopy.pieces.at(oldPosition)->move( gameCopy,fieldMap[b] );
	
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
    std::bitset<64> pawnBits(piece.getPossibleMoves());
    std::cout << pawnBits;exit(1);
    exit(1);

    piece.setPossibleMoves(bit.to_ullong());
  }

};};

#endif
