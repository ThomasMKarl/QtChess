#include "include/queen.h"

  Queen(Board &game, unsigned short int pos, std::string col = "white", bool ig = true)
  {
    position = 0b0000000000000000000000000000000000000000000000000000000000000001 << pos;
    color = col;
    ingame = ig;
    
    game.queens = game.queens | position;    
    if(color == "white") game.white = game.white | position;
    if(color == "black") game.black = game.black | position;
  }
  
  void movegen(Board &game)
  {
    int pos = log2(position);
    
    unsigned long long int shift;
    moves = 0b0000000000000000000000000000000000000000000000000000000000000000;
    
    /////////////////////////////Bishop-moves    
    for(unsigned short int i = 0; i < this->ul[pos]; i++)
    {
      shift = 0b0000000000000000000000000000000000000000000000000000000000000001 << 9*(i+1);
      if(color == "white" && (shift & game.white) != 0) break;
      if(color == "white" && (shift & game.black) != 0)
      {
	moves = moves | shift;
	break;
      }

      if(color == "black" && (shift & game.black) != 0) break;
      if(color == "black" && (shift & game.white) != 0)
      {
	moves = moves | shift;
	break;
      }
      
      moves = moves | shift;
    }

    for(unsigned short int i = 0; i < this->dr[pos]; i++)
    {
      shift = 0b0000000000000000000000000000000000000000000000000000000000000001 >> 9*(i+1);
      if(color == "white" && (shift & game.white) != 0) break;
      if(color == "white" && (shift & game.black) != 0)
      {
	moves = moves | shift;
	break;
      }

      if(color == "black" && (shift & game.black) != 0) break;
      if(color == "black" && (shift & game.white) != 0)
      {
	moves = moves | shift;
	break;
      }
      
      moves = moves | shift;
    }

    for(unsigned short int i = 0; i < this->ur[pos]; i++)
    {
      shift = 0b0000000000000000000000000000000000000000000000000000000000000001 << 7*(i+1);
      if(color == "white" && (shift & game.white) != 0) break;
      if(color == "white" && (shift & game.black) != 0)
      {
	moves = moves | shift;
	break;
      }

      if(color == "black" && (shift & game.black) != 0) break;
      if(color == "black" && (shift & game.white) != 0)
      {
	moves = moves | shift;
	break;
      }
      
      moves = moves | shift;
    }

    for(unsigned short int i = 0; i < this->dl[pos]; i++)
    {
      shift = 0b0000000000000000000000000000000000000000000000000000000000000001 >> 7*(i+1);
      if(color == "white" && (shift & game.white) != 0) break;
      if(color == "white" && (shift & game.black) != 0)
      {
	moves = moves | shift;
	break;
      }

      if(color == "black" && (shift & game.black) != 0) break;
      if(color == "black" && (shift & game.white) != 0)
      {
	moves = moves | shift;
	break;
      }
      
      moves = moves | shift;
    }
    

    //////////////////////////Rook-moves
    for(unsigned short int i = 0; i < this->u[pos]; i++)
    {
      shift = 0b0000000000000000000000000000000000000000000000000000000000000001 << 8*(i+1);
      if(color == "white" && (shift & game.white) != 0) break;
      if(color == "white" && (shift & game.black) != 0)
      {
	moves = moves | shift;
	break;
      }

      if(color == "black" && (shift & game.black) != 0) break;
      if(color == "black" && (shift & game.white) != 0)
      {
	moves = moves | shift;
	break;
      }
      
      moves = moves | shift;
    }

    for(unsigned short int i = 0; i < this->d[pos]; i++)
    {
      shift = 0b0000000000000000000000000000000000000000000000000000000000000001 >> 8*(i+1);
      if(color == "white" && (shift & game.white) != 0) break;
      if(color == "white" && (shift & game.black) != 0)
      {
	moves = moves | shift;
	break;
      }

      if(color == "black" && (shift & game.black) != 0) break;
      if(color == "black" && (shift & game.white) != 0)
      {
	moves = moves | shift;
	break;
      }
      
      moves = moves | shift;
    }

    for(unsigned short int i = 0; i < this->r[pos]; i++)
    {
      shift = 0b0000000000000000000000000000000000000000000000000000000000000001 << (i+1);
      if(color == "white" && (shift & game.white) != 0) break;
      if(color == "white" && (shift & game.black) != 0)
      {
	moves = moves | shift;
	break;
      }

      if(color == "black" && (shift & game.black) != 0) break;
      if(color == "black" && (shift & game.white) != 0)
      {
	moves = moves | shift;
	break;
      }
      
      moves = moves | shift;
    }

    for(unsigned short int i = 0; i < this->l[pos]; i++)
    {
      shift = 0b0000000000000000000000000000000000000000000000000000000000000001 >> (i+1);
      if(color == "white" && (shift & game.white) != 0) break;
      if(color == "white" && (shift & game.black) != 0)
      {
	moves = moves | shift;
	break;
      }

      if(color == "black" && (shift & game.black) != 0) break;
      if(color == "black" && (shift & game.white) != 0)
      {
	moves = moves | shift;
	break;
      }
      
      moves = moves | shift;
    }
  };

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
    game.queens = game.queens & ~position;     
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
    game.queens = game.queens | position;
    if(color == "white") game.white = game.white | position;
    if(color == "black") game.black = game.black | position;
  }
