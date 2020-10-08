#ifndef BISHOP_H
#define BISHOP_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <bitset>
#include <vector>

#include "include/board.h"
#include "include/piece.h"

class Bishop: public Piece
{
 public:
  Bishop(Board &game, unsigned short int pos, std::string col = "white", bool ig = true);
  void movegen(Board &game);
  void move(Board &game, std::string m);

 private:
  unsigned short int ul[64] = {7,6,5,4,3,2,1,0,
		               6,6,5,4,3,2,1,0,
                               5,5,5,4,3,2,1,0,
                               4,4,4,4,3,2,1,0,
                               3,3,3,3,3,2,1,0,
                               2,2,2,2,2,2,1,0,
                               1,1,1,1,1,1,1,0,
                               0,0,0,0,0,0,0,0};
  unsigned short int ur[64] = {0,1,2,3,4,5,6,7,
                               0,1,2,3,4,5,6,6,
                               0,1,2,3,4,5,5,5,
                               0,1,2,3,4,4,4,4,
                               0,1,2,3,3,3,3,3,
                               0,1,2,2,2,2,2,2,
                               0,1,1,1,1,1,1,1,
                               0,0,0,0,0,0,0,0};
  unsigned short int dl[64] = {0,0,0,0,0,0,0,0,
                               1,1,1,1,1,1,1,0,
                               2,2,2,2,2,2,1,0,
                               3,3,3,3,3,2,1,0,
                               4,4,4,4,3,2,1,0,
                               5,5,5,4,3,2,1,0,
                               6,6,5,4,3,2,1,0,
                               7,6,5,4,3,2,1,0};
  unsigned short int dr[64] = {0,0,0,0,0,0,0,0,
			       0,1,1,1,1,1,1,1,
                               0,1,2,2,2,2,2,2,
			       0,1,2,3,3,3,3,3,
			       0,1,2,3,4,4,4,4,
			       0,1,2,3,4,5,5,5,
			       0,1,2,3,4,5,6,6,
			       0,1,2,3,4,5,6,7};
};

#endif
