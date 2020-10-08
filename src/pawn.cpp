#include "include/pawn.h"

  Pawn(Board &game, unsigned short int pos, std::string col = "white", bool ig = true)
  {
    position = 0b0000000000000000000000000000000000000000000000000000000000000001 << pos;
    color = col;
    ingame = ig;
    
    game.pawns = game.pawns | position;    
    if(color == "white") game.white = game.white | position;
    if(color == "black") game.black = game.black | position;
  }

  void movegen()
  {
    unsigned long long int onestep, doublestep = 0;
    unsigned long long int hit;
    
    if(color == "white")
    {
      onestep    = position << 8 | (game.black & game.white);
      if(!moved) doublestep = onestep  << 8 | (game.black & game.white);
      hit = position << 7 & game.black & position << 9 & game.black;
    }
    else
    {
      onestep    = position >> 8 | (game.black & game.white);
      if(!moved) doublestep = onestep  >> 8 | (game.black & game.white);
      hit = position >> 7 & game.white & position >> 9 & game.white;
    }

    moves = onestep | doublestep | hit;
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
    game.pawns = game.pawns & ~position;     
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
    if(position >= pow(2,56) || position <= pow(2,7))
    {
      trans();
    }
    else
    {
      game.pawns = game.pawns | position;
      if(color == "white") game.white = game.white | position;
      if(color == "black") game.black = game.black | position;
    } 
  }

  void trans(){}
