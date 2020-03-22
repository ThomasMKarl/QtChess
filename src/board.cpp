#include "include/board.h"

  Board()
  {      
    white_cancastle_short = true;
    white_cancastle_long  = true;
    black_cancastle_short = true;
    black_cancastle_long  = true;

    white_check     = false;
    whitw_checkmate = false;
    black_check     = false;
    black_checkmate = false;

    pawns   = 0b0000000011111111000000000000000000000000000000001111111100000000;
    knights = 0b0100001000000000000000000000000000000000000000000000000001000010;  
    bishops = 0b0010010000000000000000000000000000000000000000000000000000100100;  
    rooks   = 0b1000000100000000000000000000000000000000000000000000000010000001;  
    queens  = 0b0001000000000000000000000000000000000000000000000000000000010000;  
    kings   = 0b0000100000000000000000000000000000000000000000000000000000001000;
    white   = 0b0000000000000000000000000000000000000000000000001111111111111111; 
    black   = 0b1111111111111111000000000000000000000000000000000000000000000000;
    
    //////////////////////////////////////////////////
    
    for(unsigned short int i = 48; i < 56; i++)
    {
      Pawn pawn(this, i, "black", true);
      bpawn.push_back(pawn);
    }
  
    Rook rook1(this, 56, "black", true);
    brook.push_back(rook1);
    Rook rook2(this, 63, "black", true);
    brook.push_back(rook2);
  
    Bishop bishop1(this, 58, "black", true);
    bbishop.push_back(bishop1);
    Bishop bishop2(this, 61, "black", true);
    bbishop.push_back(bishop2);

    Knight knight1(this, 57, "black", true);
    bknight.push_back(knight1);
    Knight knight2(this, 62, "black", true);
    bknight.push_back(knight2);

    Queen queen1(this, 60, "black", true);
    bqueen.push_back(queen1);

    King king1(this, 59, "black");
    bking.push_back(king1);
  
    //////////////////////////////////////////////////
  
    for(long int i=8; i<16; i++)
    {
      Pawn pawn(this, i, "white", true);
      wpawn.push_back(pawn);
    }
  
    Rook rook3(this, 0, "white", true);
    wrook.push_back(rook3);
    Rook rook4(this, 7, "white", true);
    wrook.push_back(rook4);
  
    Bishop bishop3(this, 2, "white", true);
    wbishop.push_back(bishop3);
    Bishop bishop4(this, 5, "white", true);
    wbishop.push_back(bishop4);

    Knight knight3(this, 1, "white", true);
    wknight.push_back(knight3);
    Knight knight4(this, 6, "white", true);
    wknight.push_back(knight4);

    Queen queen2(this, 4, "white", true);
    wqueen.push_back(queen2);

    King king2(this, 3, "white");
    wking.push_back(king2);
  };

  void print_pawn() const
  {
    std::bitset<64> x(pawns);
    std::cout << x << std::endl;
  }
