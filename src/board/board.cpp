#include "board/board.h"
#include "piece/static.h"

  template<typename T>
  void qtc::Board::createPiece(const unsigned short int position, const bool isWhite)
  {
    //pieces.insert({position, std::make_shared<T>(*this,position,isWhite)});
    pieces.insert({position, T{*this,position,isWhite}});
  }
  template void qtc::Board::createPiece<qtc::pc::Pawn>
    (const unsigned short int position, const bool isWhite);
/*template void qtc::Board::createPiece<qtc::pc::Knight>
    (const unsigned short int position, const bool isWhite);
  template void qtc::Board::createPiece<qtc::pc::Bishop>
    (const unsigned short int position, const bool isWhite);
  template void qtc::Board::createPiece<qtc::pc::Rook>
    (const unsigned short int position, const bool isWhite);
  template void qtc::Board::createPiece<qtc::pc::Queen>
    (const unsigned short int position, const bool isWhite);
  template void qtc::Board::createPiece<qtc::pc::King>
  (const unsigned short int position, const bool isWhite);*/

  bool qtc::Board::operator==(const Board &rhs) const
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

  void qtc::Board::printPositionsBinary() const
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

/*bool qtc::Board::positionsMatchWithPieces() const
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
    }*/

  std::vector<std::string> qtc::Board::generateWhiteMoves() 
  {
    std::vector<std::string> whiteMoves{};
    
    qtc::MoveGenerator moveGen{*this};
    
    for(const auto& [position, piece] : pieces)
    {
        if(binaryField[position] & whitePositions)
        {
	  mpark::visit(moveGen,piece);
	  std::vector<std::string> moves =
	    moveGen.getPossibleMoves();
	  std::copy(moves.begin(), moves.end(), whiteMoves.end());
        }
    }

    return whiteMoves;
  }

  std::vector<std::string> qtc::Board::generateBlackMoves()
  {
    std::vector<std::string> blackMoves{};
    
    qtc::MoveGenerator moveGen{*this};
    
    for(const auto& [position, piece] : pieces)
    {
        if(binaryField[position] & blackPositions)
        {
	  mpark::visit(moveGen,piece);
	  std::vector<std::string> moves =
	    moveGen.getPossibleMoves();
	  std::copy(moves.begin(), moves.end(), blackMoves.end());
        }
    }

    return blackMoves;
  }

  std::vector<std::string> qtc::Board::update()
  {
    std::vector<std::string> possibleMoves{};
    
    if(whiteToMove)
    {     
      if(threatenedFields & kingPositions & whitePositions)
	whiteIsChecked = false;
      else
	whiteIsChecked = true;
      
      possibleMoves = generateWhiteMoves();

      if(possibleMoves.empty())
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

      if(possibleMoves.empty())
      {
	blackIsStalemate = true;
	if(whiteIsChecked)
	{
	  blackIsStalemate = false;
	  blackIsCheckmate = true;
	}
      }
    }

    threatenedFields = computeThreatenedFields(possibleMoves);
    
    return possibleMoves;
  }

