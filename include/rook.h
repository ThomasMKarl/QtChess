#ifndef ROOK_H
#define ROOK_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <bitset>
#include <vector>

#include "include/board.h"
#include "include/piece.h"

class Rook: public Piece
{
 public:
  Rook(Board &game, unsigned short int pos, std::string col = "white", bool ig = true);

  void movegen(Board &game);
  void move(Board &game, std::string m);

 private:
  unsigned short int u[64] = {7,7,7,7,7,7,7,7,
		              6,6,6,6,6,6,6,6,
		              5,5,5,5,5,5,5,5,
		              4,4,4,4,4,4,4,4,
		              3,3,3,3,3,3,3,3,
		              2,2,2,2,2,2,2,2,
		              1,1,1,1,1,1,1,1,
		              0,0,0,0,0,0,0,0};
  unsigned short int d[64] = {0,0,0,0,0,0,0,0,
		              1,1,1,1,1,1,1,1,
		              2,2,2,2,2,2,2,2,
		              3,3,3,3,3,3,3,3,
		              4,4,4,4,4,4,4,4,
		              5,5,5,5,5,5,5,5,
		              6,6,6,6,6,6,6,6,
		              7,7,7,7,7,7,7,7};
  unsigned short int l[64] = {7,6,5,4,3,2,1,0,
		              7,6,5,4,3,2,1,0,
		              7,6,5,4,3,2,1,0,
		              7,6,5,4,3,2,1,0,
		              7,6,5,4,3,2,1,0,	       
		              7,6,5,4,3,2,1,0,
		              7,6,5,4,3,2,1,0,
		              7,6,5,4,3,2,1,0};
  unsigned short int r[64] = {0,1,2,3,4,5,6,7,
		              0,1,2,3,4,5,6,7,
		              0,1,2,3,4,5,6,7,
		              0,1,2,3,4,5,6,7,
		              0,1,2,3,4,5,6,7,
		              0,1,2,3,4,5,6,7,
		              0,1,2,3,4,5,6,7,
		              0,1,2,3,4,5,6,7};
};

#endif
