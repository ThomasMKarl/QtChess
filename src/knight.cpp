#include "include/knight.h"

  Knight(Board &game, unsigned short int pos, std::string col = "white", bool ig = true)
  {
    position = 0b0000000000000000000000000000000000000000000000000000000000000001 << pos;
    color = col;
    ingame = ig;
    
    game.knights = game.knights | position;    
    if(color == "white") game.white = game.white | position;
    if(color == "black") game.black = game.black | position;
  }
  
  void movegen(Board &game)
  {
    unsigned short int pos = log2(position);
    for(unsigned short int i = 0; i < number_of_moves[pos]; i++)
    {
      if(color == "white") moves = moves | 0b0000000000000000000000000000000000000000000000000000000000000001 << mv_table[pos][i] | game.white;
      if(color == "black") moves = moves | 0b0000000000000000000000000000000000000000000000000000000000000001 << mv_table[pos][i] | game.black;
    }
  }
  
  void move(Board &game, std::string m)
  {
    unsigned long long int mv = 0b0000000000000000000000000000000000000000000000000000000000000001;
    for(unsigned short int i = 0; i < 64; i++)
    {
      if(game.map[i] == m)
      {
	mv = mv << i;
	break;
      }
    }
    if((mv & moves) != 0)
    {
      std::cout << "impossible move!" << std::endl;
      return;
    }
    
    //delete old position
    game.knights = game.knights & ~position;     
    if(color == "white") game.white = game.white & ~position;
    if(color == "black") game.black = game.black & ~position;

    //if hit delete figure position
    game.pawns   = game.pawns   & ~mv;
    game.knights = game.knights & ~mv;
    game.bishops = game.bishops & ~mv;
    game.rooks   = game.rooks   & ~mv;
    game.queens  = game.queens  & ~mv;
    
    game.white   = game.white   & ~mv;
    game.black   = game.black   & ~mv;

    //set new position
    position = mv;
    game.knights = game.knights | position;
    if(color == "white") game.white = game.white | position;
    if(color == "black") game.black = game.black | position;
  }
