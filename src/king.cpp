#include "include/king.h"

  King(Board &game, unsigned short int pos, std::string col = "white")
  {
    position = 0b0000000000000000000000000000000000000000000000000000000000000001 << pos;
    color = col;
    
    game.kings = game.kings | position;    
    if(color == "white") game.white = game.white | position;
    if(color == "black") game.black = game.black | position;

    /*for(unsigned short int i = 0; i < 64; i++)
    {
      if(i == 0)
      {
	mv_table[i].push_back(1);
	mv_table[i].push_back(8);
	mv_table[i].push_back(9);
      }
      if(i == 1)
      {
	mv_table[i].push_back(0);
	mv_table[i].push_back(2);
	mv_table[i].push_back(8);
	mv_table[i].push_back(9);
	mv_table[i].push_back(10);
      }
      if(i == 2)
      {
	mv_table[i].push_back(1);
	mv_table[i].push_back(3);
	mv_table[i].push_back(9);
	mv_table[i].push_back(10);
        mv_table[i].push_back(11);
      }
      if(i == 3)
      {
	mv_table[i].push_back(2);
	mv_table[i].push_back(4);
	mv_table[i].push_back(10);
	mv_table[i].push_back(11);
        mv_table[i].push_back(12);
      }
      if(i == 4)
      {
	mv_table[i].push_back(3);
	mv_table[i].push_back(5);
	mv_table[i].push_back(11);
	mv_table[i].push_back(12);
        mv_table[i].push_back(13);
      }
      if(i == 5)
      {
	mv_table[i].push_back(4);
	mv_table[i].push_back(6);
	mv_table[i].push_back(12);
	mv_table[i].push_back(13);
        mv_table[i].push_back(14);
      }
      if(i == 6)
      {
	mv_table[i].push_back(5);
	mv_table[i].push_back(7);
	mv_table[i].push_back(13);
        mv_table[i].push_back(14);
        mv_table[i].push_back(15);
      }
      if(i == 7)
      {
	mv_table[i].push_back(6);
	mv_table[i].push_back(14);
        mv_table[i].push_back(15);
      }
      /////////////////////////////////////
      if(i == 8)
      {
	mv_table[i].push_back(0);
	mv_table[i].push_back(1);
	mv_table[i].push_back(9);
	mv_table[i].push_back(16);
	mv_table[i].push_back(17);
      }
      if(i == 9)
      {
	mv_table[i].push_back(0);
	mv_table[i].push_back(1);
	mv_table[i].push_back(2);
	mv_table[i].push_back(8);
	mv_table[i].push_back(10);
	mv_table[i].push_back(16);
	mv_table[i].push_back(17);
	mv_table[i].push_back(18);
      }
      if(i == 10)
      {
	mv_table[i].push_back(1);
	mv_table[i].push_back(2);
	mv_table[i].push_back(3);
	mv_table[i].push_back(7);
	mv_table[i].push_back(11);
	mv_table[i].push_back(17);
	mv_table[i].push_back(18);
	mv_table[i].push_back(19);
      }
      if(i == 11)
      {
	mv_table[i].push_back(2);
	mv_table[i].push_back(3);
	mv_table[i].push_back(4);
	mv_table[i].push_back(8);
	mv_table[i].push_back(12);
	mv_table[i].push_back(18);
	mv_table[i].push_back(19);
	mv_table[i].push_back(20);
      }
      if(i == 12)
      {
	mv_table[i].push_back(3);
	mv_table[i].push_back(4);
	mv_table[i].push_back(5);
	mv_table[i].push_back(9);
	mv_table[i].push_back(13);
	mv_table[i].push_back(19);
	mv_table[i].push_back(20);
	mv_table[i].push_back(21);
      }
      if(i == 13)
      {
	mv_table[i].push_back(4);
	mv_table[i].push_back(5);
	mv_table[i].push_back(6);
	mv_table[i].push_back(10);
	mv_table[i].push_back(14);
	mv_table[i].push_back(20);
	mv_table[i].push_back(21);
	mv_table[i].push_back(22);
      }
      if(i == 14)
      {
	mv_table[i].push_back(5);
	mv_table[i].push_back(6);
	mv_table[i].push_back(7);
	mv_table[i].push_back(11);
	mv_table[i].push_back(15);
	mv_table[i].push_back(21);
	mv_table[i].push_back(22);
	mv_table[i].push_back(23);
      }
      if(i == 15)
      {
	mv_table[i].push_back(6);
	mv_table[i].push_back(7);
	mv_table[i].push_back(14);
	mv_table[i].push_back(22);
	mv_table[i].push_back(23);
      }
      /////////////////////////////////////
      if(i == 16)
      {
	mv_table[i].push_back(8);
	mv_table[i].push_back(9);
	mv_table[i].push_back(17);
	mv_table[i].push_back(24);
        mv_table[i].push_back(25);
      }
      if(i == 17)
      {
	mv_table[i].push_back(8);
	mv_table[i].push_back(9);
	mv_table[i].push_back(10);
	mv_table[i].push_back(16);
	mv_table[i].push_back(18);
	mv_table[i].push_back(24);
	mv_table[i].push_back(25);
	mv_table[i].push_back(26);
      }
      if(i == 18)
      {
	mv_table[i].push_back(9);
	mv_table[i].push_back(10);
	mv_table[i].push_back(11);
	mv_table[i].push_back(17);
	mv_table[i].push_back(19);
	mv_table[i].push_back(25);
	mv_table[i].push_back(26);
	mv_table[i].push_back(27);
      }
      if(i == 19)
      {
	mv_table[i].push_back(10);
	mv_table[i].push_back(11);
	mv_table[i].push_back(12);
	mv_table[i].push_back(18);
	mv_table[i].push_back(20);
	mv_table[i].push_back(26);
	mv_table[i].push_back(27);
	mv_table[i].push_back(28);
      }
      if(i == 20)
      {
	mv_table[i].push_back(11);
	mv_table[i].push_back(12);
	mv_table[i].push_back(13);
	mv_table[i].push_back(19);
	mv_table[i].push_back(21);
	mv_table[i].push_back(27);
	mv_table[i].push_back(28);
	mv_table[i].push_back(29);
      }
      if(i == 21)
      {
	mv_table[i].push_back(12);
	mv_table[i].push_back(13);
	mv_table[i].push_back(14);
	mv_table[i].push_back(20);
	mv_table[i].push_back(22);
	mv_table[i].push_back(28);
	mv_table[i].push_back(29);
	mv_table[i].push_back(30);
      }
      if(i == 22)
      {
	mv_table[i].push_back(13);
	mv_table[i].push_back(14);
	mv_table[i].push_back(15);
	mv_table[i].push_back(21);
	mv_table[i].push_back(23);
	mv_table[i].push_back(29);
	mv_table[i].push_back(30);
	mv_table[i].push_back(31);
      }
      if(i == 23)
      {
	mv_table[i].push_back(14);
	mv_table[i].push_back(15);
	mv_table[i].push_back(22);
	mv_table[i].push_back(30);
	mv_table[i].push_back(31);
      }
      /////////////////////////////////////
      if(i == 24)
      {
	mv_table[i].push_back(16);
	mv_table[i].push_back(17);
	mv_table[i].push_back(25);
	mv_table[i].push_back(32);
	mv_table[i].push_back(33);
      }
      if(i == 25)
      {
	mv_table[i].push_back(16);
	mv_table[i].push_back(17);
	mv_table[i].push_back(18);
	mv_table[i].push_back(24);
	mv_table[i].push_back(26);
	mv_table[i].push_back(32);
	mv_table[i].push_back(33);
	mv_table[i].push_back(34);
      }
      if(i == 26)
      {
	mv_table[i].push_back(17);
	mv_table[i].push_back(18);
	mv_table[i].push_back(19);
	mv_table[i].push_back(24);
	mv_table[i].push_back(26);
	mv_table[i].push_back(32);
	mv_table[i].push_back(33);
	mv_table[i].push_back(34);
      }
      if(i == 27)
      {
	mv_table[i].push_back(18);
	mv_table[i].push_back(19);
	mv_table[i].push_back(20);
	mv_table[i].push_back(26);
	mv_table[i].push_back(28);
	mv_table[i].push_back(34);
	mv_table[i].push_back(35);
	mv_table[i].push_back(36);
      }
      if(i == 28)
      {
	mv_table[i].push_back(19);
	mv_table[i].push_back(20);
	mv_table[i].push_back(21);
	mv_table[i].push_back(27);
	mv_table[i].push_back(29);
	mv_table[i].push_back(35);
	mv_table[i].push_back(36);
	mv_table[i].push_back(37);
      }
      if(i == 29)
      {
	mv_table[i].push_back(20);
	mv_table[i].push_back(21);
	mv_table[i].push_back(22);
	mv_table[i].push_back(28);
	mv_table[i].push_back(30);
	mv_table[i].push_back(36);
	mv_table[i].push_back(37);
	mv_table[i].push_back(38);
      }
      if(i == 30)
      {
	mv_table[i].push_back(21);
	mv_table[i].push_back(22);
	mv_table[i].push_back(23);
	mv_table[i].push_back(29);
	mv_table[i].push_back(31);
	mv_table[i].push_back(37);
	mv_table[i].push_back(38);
	mv_table[i].push_back(39);
      }
      if(i == 31)
      {
	mv_table[i].push_back(22);
	mv_table[i].push_back(23);
	mv_table[i].push_back(30);
	mv_table[i].push_back(38);
	mv_table[i].push_back(39);
      }
      /////////////////////////////////////
      if(i == 32)
      {
	mv_table[i].push_back(24);
	mv_table[i].push_back(25);
	mv_table[i].push_back(33);
	mv_table[i].push_back(40);
	mv_table[i].push_back(41);
      }
      if(i == 33)
      {
	mv_table[i].push_back(24);
	mv_table[i].push_back(25);
	mv_table[i].push_back(26);
	mv_table[i].push_back(32);
	mv_table[i].push_back(34);
	mv_table[i].push_back(40);
	mv_table[i].push_back(41);
	mv_table[i].push_back(42);
      }
      if(i == 34)
      {
	mv_table[i].push_back(25);
	mv_table[i].push_back(26);
	mv_table[i].push_back(27);
	mv_table[i].push_back(33);
	mv_table[i].push_back(35);
	mv_table[i].push_back(41);
	mv_table[i].push_back(42);
	mv_table[i].push_back(43);
      }
      if(i == 35)
      {
	mv_table[i].push_back(26);
	mv_table[i].push_back(27);
	mv_table[i].push_back(28);
	mv_table[i].push_back(34);
	mv_table[i].push_back(36);
	mv_table[i].push_back(42);
	mv_table[i].push_back(43);
	mv_table[i].push_back(44);
      }
      if(i == 36)
      {
	mv_table[i].push_back(27);
	mv_table[i].push_back(28);
	mv_table[i].push_back(29);
	mv_table[i].push_back(35);
	mv_table[i].push_back(37);
	mv_table[i].push_back(43);
	mv_table[i].push_back(44);
	mv_table[i].push_back(45);
      }
      if(i == 37)
      {
	mv_table[i].push_back(28);
	mv_table[i].push_back(29);
	mv_table[i].push_back(30);
	mv_table[i].push_back(36);
	mv_table[i].push_back(38);
	mv_table[i].push_back(44);
	mv_table[i].push_back(45);
	mv_table[i].push_back(46);
      }
      if(i == 38)
      {
	mv_table[i].push_back(29);
	mv_table[i].push_back(30);
	mv_table[i].push_back(31);
	mv_table[i].push_back(37);
	mv_table[i].push_back(39);
	mv_table[i].push_back(45);
	mv_table[i].push_back(46);
        mv_table[i].push_back(47);
      }
      if(i == 39)
      {
	mv_table[i].push_back(30);
	mv_table[i].push_back(31);
	mv_table[i].push_back(38);
	mv_table[i].push_back(46);
	mv_table[i].push_back(47);
      }
      /////////////////////////////////////
      if(i == 40)
      {
	mv_table[i].push_back(32);
	mv_table[i].push_back(33);
	mv_table[i].push_back(41);
	mv_table[i].push_back(48);
	mv_table[i].push_back(49);
      }
      if(i == 41)
      {
	mv_table[i].push_back(32);
	mv_table[i].push_back(33);
	mv_table[i].push_back(34);
	mv_table[i].push_back(40);
	mv_table[i].push_back(42);
	mv_table[i].push_back(48);
	mv_table[i].push_back(49);
	mv_table[i].push_back(50);
      }
      if(i == 42)
      {
	mv_table[i].push_back(33);
	mv_table[i].push_back(34);
	mv_table[i].push_back(35);
	mv_table[i].push_back(41);
	mv_table[i].push_back(43);
	mv_table[i].push_back(49);
	mv_table[i].push_back(50);
	mv_table[i].push_back(51);
      }
      if(i == 43)
      {
	mv_table[i].push_back(34);
	mv_table[i].push_back(35);
	mv_table[i].push_back(36);
	mv_table[i].push_back(42);
	mv_table[i].push_back(44);
	mv_table[i].push_back(50);
	mv_table[i].push_back(51);
	mv_table[i].push_back(52);
      }
      if(i == 44)
      {
	mv_table[i].push_back(35);
	mv_table[i].push_back(36);
	mv_table[i].push_back(37);
	mv_table[i].push_back(43);
	mv_table[i].push_back(45);
	mv_table[i].push_back(51);
	mv_table[i].push_back(52);
	mv_table[i].push_back(53);
      }
      if(i == 45)
      {
	mv_table[i].push_back(36);
	mv_table[i].push_back(37);
	mv_table[i].push_back(38);
	mv_table[i].push_back(44);
	mv_table[i].push_back(46);
	mv_table[i].push_back(52);
	mv_table[i].push_back(53);
	mv_table[i].push_back(54);
      }
      if(i == 46)
      {
	mv_table[i].push_back(37);
	mv_table[i].push_back(38);
	mv_table[i].push_back(39);
	mv_table[i].push_back(45);
	mv_table[i].push_back(47);
	mv_table[i].push_back(53);
	mv_table[i].push_back(54);
	mv_table[i].push_back(55);
      }
      if(i == 47)
      {
	mv_table[i].push_back(38);
	mv_table[i].push_back(39);
	mv_table[i].push_back(46);
	mv_table[i].push_back(54);
	mv_table[i].push_back(55);
      }
      /////////////////////////////////////
      if(i == 48)
      {
	mv_table[i].push_back(40);
	mv_table[i].push_back(41);
	mv_table[i].push_back(49);
	mv_table[i].push_back(56);
	mv_table[i].push_back(57);
      }
      if(i == 49)
      {
	mv_table[i].push_back(40);
	mv_table[i].push_back(41);
	mv_table[i].push_back(42);
	mv_table[i].push_back(48);
	mv_table[i].push_back(50);
	mv_table[i].push_back(56);
	mv_table[i].push_back(57);
	mv_table[i].push_back(58);
      }
      if(i == 50)
      {
	mv_table[i].push_back(41);
	mv_table[i].push_back(42);
	mv_table[i].push_back(43);
	mv_table[i].push_back(49);
	mv_table[i].push_back(51);
	mv_table[i].push_back(57);
	mv_table[i].push_back(58);
	mv_table[i].push_back(59);
      }
      if(i == 51)
      {
	mv_table[i].push_back(42);
	mv_table[i].push_back(43);
	mv_table[i].push_back(44);
	mv_table[i].push_back(50);
	mv_table[i].push_back(52);
	mv_table[i].push_back(58);
	mv_table[i].push_back(59);
	mv_table[i].push_back(60);
      }
      if(i == 52)
      {
	mv_table[i].push_back(43);
	mv_table[i].push_back(44);
	mv_table[i].push_back(45);
	mv_table[i].push_back(51);
	mv_table[i].push_back(53);
	mv_table[i].push_back(59);
	mv_table[i].push_back(60);
	mv_table[i].push_back(61);
      }
      if(i == 53)
      {
	mv_table[i].push_back(44);
	mv_table[i].push_back(45);
	mv_table[i].push_back(46);
	mv_table[i].push_back(52);
	mv_table[i].push_back(54);
	mv_table[i].push_back(60);
	mv_table[i].push_back(61);
	mv_table[i].push_back(62);
      }
      if(i == 54)
      {
	mv_table[i].push_back(45);
	mv_table[i].push_back(46);
	mv_table[i].push_back(47);
	mv_table[i].push_back(53);
	mv_table[i].push_back(55);
	mv_table[i].push_back(61);
	mv_table[i].push_back(62);
	mv_table[i].push_back(63);
      }
      if(i == 55)
      {
	mv_table[i].push_back(46);
	mv_table[i].push_back(47);
	mv_table[i].push_back(54);
	mv_table[i].push_back(62);
	mv_table[i].push_back(63);
      }
      /////////////////////////////////////
      if(i == 56)
      {
	mv_table[i].push_back(48);
	mv_table[i].push_back(49);
	mv_table[i].push_back(57);
      }
      if(i == 57)
      {
	mv_table[i].push_back(48);
	mv_table[i].push_back(49);
	mv_table[i].push_back(50);
	mv_table[i].push_back(56);
	mv_table[i].push_back(58);
      }
      if(i == 58)
      {
	mv_table[i].push_back(49);
	mv_table[i].push_back(50);
	mv_table[i].push_back(51);
	mv_table[i].push_back(57);
	mv_table[i].push_back(59);
      }
      if(i == 59)
      {
	mv_table[i].push_back(50);
	mv_table[i].push_back(51);
	mv_table[i].push_back(52);
	mv_table[i].push_back(58);
	mv_table[i].push_back(60);
      }
      if(i == 60)
      {
	mv_table[i].push_back(51);
	mv_table[i].push_back(52);
	mv_table[i].push_back(53);
	mv_table[i].push_back(59);
	mv_table[i].push_back(61);
      }
      if(i == 61)
      {
	mv_table[i].push_back(52);
	mv_table[i].push_back(53);
	mv_table[i].push_back(54);
	mv_table[i].push_back(60);
	mv_table[i].push_back(62);
      }
      if(i == 62)
      {
	mv_table[i].push_back(53);
	mv_table[i].push_back(54);
	mv_table[i].push_back(55);
	mv_table[i].push_back(61);
	mv_table[i].push_back(63);
      }
      if(i == 63)
      {
	mv_table[i].push_back(54);
	mv_table[i].push_back(55);
	mv_table[i].push_back(62);
      }
      }*/
  }
  
  void movegen(Board &game)
  {
    unsigned short int pos = log2(position);
    for(unsigned short int i = 0; i < number_of_moves[pos]; i++)
    {
      if(color == "white") moves = moves | 0b0000000000000000000000000000000000000000000000000000000000000001 << mv_table[pos][i] | game.white;
      else                 moves = moves | 0b0000000000000000000000000000000000000000000000000000000000000001 << mv_table[pos][i] | game.black;
    }
    
    if(color == "white" && game.white_cancastle_long  && pos ==  3)
      moves = moves | 0b0000000000000000000000000000000000000000000000000000000000000001 << 2;
    if(color == "white" && game.white_cancastle_short && pos ==  3)
      moves = moves | 0b0000000000000000000000000000000000000000000000000000000000000001 >> 2;

    if(color == "black" && game.white_cancastle_long  && pos == 59)
      moves = moves | 0b0000000000000000000000000000000000000000000000000000000000000001 << 2;
    if(color == "black" && game.white_cancastle_short && pos == 59)
      moves = moves | 0b0000000000000000000000000000000000000000000000000000000000000001 >> 2;
  }
  
  void move(Board &game, std::string m)
  {
    if(m == "0-0"   && color == "white") m = "g1";
    if(m == "0-0-0" && color == "white") m = "c1";
    if(m == "0-0"   && color == "black") m = "g8";
    if(m == "0-0-0" && color == "black") m = "c8";
    
    if(color == "white")
    {
      game.white_cancastle_long  = false;
      game.white_cancastle_short = false;
    }
    if(color == "black")
    {
      game.black_cancastle_long  = false;
      game.black_cancastle_short = false;
    }

    //####if(Rochade) turm...
		  
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
      std::cerr << "impossible move!" << std::endl;
      return;
    }
    
    //delete old position
    game.kings = game.kings & ~position;     
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
    game.kings = game.kings | position;
    if(color == "white") game.white = game.white | position;
    if(color == "black") game.black = game.black | position;
  }
