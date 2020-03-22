#ifndef PAWN_H
#define PAWN_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <bitset>
#include <vector>

#include "include/board.h"
#include "include/piece.h"

class Pawn: public Piece
{
 public:
  Pawn(Board &game, unsigned short int pos, std::string col = "white", bool ig = true);

  void movegen();
  void move(Board &game, std::string m);
  void trans(){};
  
 private:
  bool leftep  = false;
  bool rightep = false;
  bool moved = false;
  
};

#endif
