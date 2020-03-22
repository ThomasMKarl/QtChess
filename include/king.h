#ifndef KING_H
#define KING_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <bitset>
#include <vector>

#include "include/board.h"
#include "include/piece.h"

class King: public Piece
{
 public:
  King(Board &game, unsigned short int pos, std::string col = "white");
  
  void movegen(Board &game);
  void move(Board &game, std::string m);

 private:
  unsigned short int number_of_moves[64] = {};
  unsigned short int mv_table[64][8] = {};
};

#endif
