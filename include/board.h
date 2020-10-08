#ifndef BOARD_H
#define BOARD_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <bitset>
#include <vector>

#include "include/pawn.h"
#include "include/knight.h"
#include "include/bishop.h"
#include "include/rook.h"
#include "include/queen.h"
#include "include/king.h"

class Board
{
 public:
  Board();

  void print_pawn() const;

  //private:  
  unsigned long long int pawns   = 0;
  unsigned long long int knights = 0;  
  unsigned long long int bishops = 0;  
  unsigned long long int rooks   = 0;  
  unsigned long long int queens  = 0;  
  unsigned long long int kings   = 0;
  unsigned long long int white   = 0; 
  unsigned long long int black   = 0;
  
  std::vector<Pawn>   bpawn;
  std::vector<Knight> bknight;
  std::vector<Bishop> bbishop;
  std::vector<Rook>   brook;
  std::vector<Queen>  bqueen;
  std::vector<King>   bking;

  std::vector<Pawn>   wpawn;
  std::vector<Knight> wknight;
  std::vector<Bishop> wbishop;
  std::vector<Rook>   wrook;
  std::vector<Queen>  wqueen;
  std::vector<King>   wking;

  std::string map[64] = {"h1", "g1", "f1", "e1", "d1", "c1", "b1", "a1", "h2", "g2", "f2", "e2", "d2", "c2", "b2", "a2", "h3", "g3", "f3", "e3", "d3", "c3", "b3", "a3", "h4", "g4", "f4", "e4", "d4", "c4", "b4", "a4", "h5", "g5", "f5", "e5", "d5", "c5", "b5", "a5", "h6", "g6", "f6", "e6", "d6", "c6", "b6", "a6", "h7", "g7", "f7", "e7", "d7", "c7", "b7", "a7", "h8", "g8", "f8", "e8", "d8", "c8", "b8", "a8"};
  
  bool white_cancastle_short = true;
  bool white_cancastle_long  = true;
  bool black_cancastle_short = true;
  bool black_cancastle_long  = true;

  bool white_check     = false;
  bool whitw_checkmate = false;
  bool black_check     = false;
  bool black_checkmate = false;
};
  
#endif
