#ifndef DEF_H
#define DEF_H

class RookMoveTable
{
 public:
  std::array<unsigned short int, 64> upper = {7,7,7,7,7,7,7,7,
		                              6,6,6,6,6,6,6,6,
		                              5,5,5,5,5,5,5,5,
		                              4,4,4,4,4,4,4,4,
		                              3,3,3,3,3,3,3,3,
		                              2,2,2,2,2,2,2,2,
		                              1,1,1,1,1,1,1,1,
		                              0,0,0,0,0,0,0,0};
  
  std::array<unsigned short int, 64> lower = {0,0,0,0,0,0,0,0,
		                              1,1,1,1,1,1,1,1,
		                              2,2,2,2,2,2,2,2,
		                              3,3,3,3,3,3,3,3,
		                              4,4,4,4,4,4,4,4,
		                              5,5,5,5,5,5,5,5,
		                              6,6,6,6,6,6,6,6,
		                              7,7,7,7,7,7,7,7};
  
  std::array<unsigned short int, 64> left  = {7,6,5,4,3,2,1,0,
		                              7,6,5,4,3,2,1,0,
		                              7,6,5,4,3,2,1,0,
		                              7,6,5,4,3,2,1,0,
		                              7,6,5,4,3,2,1,0,	       
		                              7,6,5,4,3,2,1,0,
		                              7,6,5,4,3,2,1,0,
		                              7,6,5,4,3,2,1,0};
  
  std::array<unsigned short int, 64> right = {0,1,2,3,4,5,6,7,
		                              0,1,2,3,4,5,6,7,
		                              0,1,2,3,4,5,6,7,
		                              0,1,2,3,4,5,6,7,
		                              0,1,2,3,4,5,6,7,
		                              0,1,2,3,4,5,6,7,
		                              0,1,2,3,4,5,6,7,
		                              0,1,2,3,4,5,6,7};
};
static const RookMoveTable rookMoveTable{};

class BishopMoveTable
{
 public:
  std::array<unsigned short int, 64> upperLeft  = {7,6,5,4,3,2,1,0,
		                                   6,6,5,4,3,2,1,0,
                                                   5,5,5,4,3,2,1,0,
                                                   4,4,4,4,3,2,1,0,
                                                   3,3,3,3,3,2,1,0,
                                                   2,2,2,2,2,2,1,0,
                                                   1,1,1,1,1,1,1,0,
                                                   0,0,0,0,0,0,0,0};
  
  std::array<unsigned short int, 64> upperRight = {0,1,2,3,4,5,6,7,
                                                   0,1,2,3,4,5,6,6,
                                                   0,1,2,3,4,5,5,5,
                                                   0,1,2,3,4,4,4,4,
                                                   0,1,2,3,3,3,3,3,
                                                   0,1,2,2,2,2,2,2,
                                                   0,1,1,1,1,1,1,1,
                                                   0,0,0,0,0,0,0,0};
  
  std::array<unsigned short int, 64> lowerLeft  = {0,0,0,0,0,0,0,0,
                                                   1,1,1,1,1,1,1,0,
                                                   2,2,2,2,2,2,1,0,
                                                   3,3,3,3,3,2,1,0,
                                                   4,4,4,4,3,2,1,0,
                                                   5,5,5,4,3,2,1,0,
                                                   6,6,5,4,3,2,1,0,
                                                   7,6,5,4,3,2,1,0};
  
  std::array<unsigned short int, 64> lowerRight = {0,0,0,0,0,0,0,0,
                                                   0,1,1,1,1,1,1,1,
                                                   0,1,2,2,2,2,2,2,
			                           0,1,2,3,3,3,3,3,
			                           0,1,2,3,4,4,4,4,
			                           0,1,2,3,4,5,5,5,
			                           0,1,2,3,4,5,6,6,
			                           0,1,2,3,4,5,6,7};
};
static const BishopMoveTable bishopMoveTable{};

using KingMoveTable = std::array<unsigned long long int, 64>;
static const KingMoveTable kingMoveTable{
  //Row 1
  0b0000001100000010,//h
  0b0000011100000101,//g
  0b0000111000001010,//f
  0b0001110000010100,//e
  0b0011100000101000,//d
  0b0111000001010000,//c
  0b1110000010100000,//b
  0b1100000001000000,//a
  //Row 2
  0b000000110000001000000011,//h
  0b000001110000010100000111,//g
  0b000011100000101000001110,//f
  0b000111000001010000011100,//e
  0b001110000010100000111000,//d
  0b011100000101000001110000,//c
  0b111000001010000011100000,//b
  0b110000000100000011000000,//a
  //Row 3
  0b00000011000000100000001100000000,//h
  0b00000111000001010000011100000000,//g
  0b00001110000010100000111000000000,//f
  0b00011100000101000001110000000000,//e
  0b00111000001010000011100000000000,//d
  0b01110000010100000111000000000000,//c
  0b11100000101000001110000000000000,//b
  0b11000000010000001100000000000000,//a
  //Row 4
  0b0000001100000010000000110000000000000000,//h
  0b0000011100000101000001110000000000000000,//g
  0b0000111000001010000011100000000000000000,//f
  0b0001110000010100000111000000000000000000,//e
  0b0011100000101000001110000000000000000000,//d
  0b0111000001010000011100000000000000000000,//c
  0b1110000010100000111000000000000000000000,//b
  0b1100000001000000110000000000000000000000,//a
  //Row 5
  0b000000110000001000000011000000000000000000000000,//h
  0b000001110000010100000111000000000000000000000000,//g
  0b000011100000101000001110000000000000000000000000,//f
  0b000111000001010000011100000000000000000000000000,//e
  0b001110000010100000111000000000000000000000000000,//d
  0b011100000101000001110000000000000000000000000000,//c
  0b111000001010000011100000000000000000000000000000,//b
  0b110000000100000011000000000000000000000000000000,//a
  //Row 6
  0b00000011000000010000001100000000000000000000000000000000,//h
  0b00000111000001010000011100000000000000000000000000000000,//g
  0b00001110000010100000111000000000000000000000000000000000,//f
  0b00011100000101000001110000000000000000000000000000000000,//e
  0b00111000001010000011100000000000000000000000000000000000,//d
  0b01110000010100000111000000000000000000000000000000000000,//c
  0b11100000101000001110000000000000000000000000000000000000,//b
  0b11000000010000001100000000000000000000000000000000000000,//a
  //Row 7
  0b0000001100000010000000110000000000000000000000000000000000000000,//h
  0b0000011100000101000001110000000000000000000000000000000000000000,//g
  0b0000111000001010000011100000000000000000000000000000000000000000,//f
  0b0001110000010100000111000000000000000000000000000000000000000000,//e
  0b0011100000101000001110000000000000000000000000000000000000000000,//d
  0b0111000001010000011100000000000000000000000000000000000000000000,//c
  0b1110000010100000111000000000000000000000000000000000000000000000,//b
  0b1100000001000000110000000000000000000000000000000000000000000000,//a
  //Row 8
  0b0000001000000011000000000000000000000000000000000000000000000000,//h
  0b0000010100000111000000000000000000000000000000000000000000000000,//g
  0b0000101000001110000000000000000000000000000000000000000000000000,//f
  0b0001010000011100000000000000000000000000000000000000000000000000,//e
  0b0010100000111000000000000000000000000000000000000000000000000000,//d
  0b0101000001110000000000000000000000000000000000000000000000000000,//c
  0b1010000011100000000000000000000000000000000000000000000000000000,//b
  0b0100000011000000000000000000000000000000000000000000000000000000 //a
};

using KnightMoveTable = std::array<unsigned long long int, 64>;
static const KnightMoveTable knightMoveTable{
  //Row 1
  0b000000100000010000000000,//h
  0b000001010000100000000000,//g
  0b000010100001000100000000,//f
  0b000101000010001000000000,//e
  0b001010000100010000000000,//d
  0b010100001000100000000000,//c
  0b101000000001000000000000,//b
  0b010000000010000000000000,//a
  //Row 2
  0b00000010000010000000000000000100,//h
  0b00000101000100000000000000001000,//g
  0b00001010001000010000000000010001,//f
  0b00010100010000100000000000100010,//e
  0b00101000100001000000000001000100,//d
  0b01010001000010000000000010001000,//c
  0b10100000000100000000000000010000,//b
  0b01000000001000000000000000100000,//a
  //Row 3
  0b0000001000000100000000000000010000000010,//h
  0b0000010100001000000000000000100000000101,//g
  0b0000101000010001000000000001000100001010,//f
  0b0001010000100010000000000010001000010100,//e
  0b0010100001000100000000000100010000101000,//d
  0b0101000010001000000000001000100001010000,//c
  0b1010000000010000000000000001000010100000,//b
  0b0100000000100000000000000010000001000000,//a
  //Row 4
  0b000000100000010000000000000001000000001000000000,//h
  0b000001010000100000000000000010000000010100000000,//g
  0b000010100001000100000000000100010000101000000000,//f
  0b000101000010001000000000001000100001010000000000,//e
  0b001010000100010000000000010001000010100000000000,//d
  0b010100001000100000000000100010000101000000000000,//c
  0b101000000001000000000000000100001010000000000000,//b
  0b010000000010000000000000001000000100000000000000,//a
  //Row 5
  0b00000010000001000000000000000100000000100000000000000000,//h
  0b00000101000010000000000000001000000001010000000000000000,//g
  0b00001010000100010000000000010001000010100000000000000000,//f
  0b00010100001000100000000000100010000101000000000000000000,//e
  0b00101000010001000000000001000100001010000000000000000000,//d
  0b01010000100010000000000010001000010100000000000000000000,//c
  0b10100000000100000000000000010000101000000000000000000000,//b
  0b01000000001000000000000000100000010000000000000000000000,//a
  //Row 6
  0b0000001000000100000000000000010000000010000000000000000000000000,//h
  0b0000010100001000000000000000100000000101000000000000000000000000,//g
  0b0000101000010001000000000001000100001010000000000000000000000000,//f
  0b0001010000100010000000000010001000010100000000000000000000000000,//e
  0b0010100001000100000000000100010000101000000000000000000000000000,//d
  0b0101000010001000000000001000100001010000000000000000000000000000,//c
  0b1010000000010000000000000001000010100000000000000000000000000000,//b
  0b0100000000100000000000000010000001000000000000000000000000000000,//a
  //Row 7
  0b0000010000000000000010000000100000000000000000000000000000000000,//h
  0b0000100000000000000100000001010000000000000000000000000000000000,//g
  0b0001000100000000001000100010100000000000000000000000000000000000,//f
  0b0010001000000000010001000101000000000000000000000000000000000000,//e
  0b0100010000000000100010001010000000000000000000000000000000000000,//d
  0b1000100000000001000100010100000000000000000000000000000000000000,//c
  0b0001000000000000001000101000000000000000000000000000000000000000,//b
  0b0010000000000000010000010000000000000000000000000000000000000000,//a
  //Row 8
  0b00000100000000100000000000000000000000000000000000000000,//h
  0b00001000000001010000000000000000000000000000000000000000,//g
  0b00010001000010100000000000000000000000000000000000000000,//f
  0b00100010000101000000000000000000000000000000000000000000,//e
  0b01000100001010000000000000000000000000000000000000000000,//d
  0b10001000010100000000000000000000000000000000000000000000,//c
  0b00010000101000000000000000000000000000000000000000000000,//b
  0b00100000010000000000000000000000000000000000000000000000//a
};

static const std::array<std::string, 64> fieldMap {
  "h1", "g1", "f1", "e1", "d1", "c1", "b1", "a1",
  "h2", "g2", "f2", "e2", "d2", "c2", "b2", "a2",
  "h3", "g3", "f3", "e3", "d3", "c3", "b3", "a3",
  "h4", "g4", "f4", "e4", "d4", "c4", "b4", "a4",
  "h5", "g5", "f5", "e5", "d5", "c5", "b5", "a5",
  "h6", "g6", "f6", "e6", "d6", "c6", "b6", "a6",
  "h7", "g7", "f7", "e7", "d7", "c7", "b7", "a7",
  "h8", "g8", "f8", "e8", "d8", "c8", "b8", "a8"
};

enum Moves
{
  h1 =  0, g1 =  1, f1 =  2, e1 =  3, d1 =  4, c1 =  5, b1 =  6, a1 =  7, 
  h2 =  8, g2 =  9, f2 = 10, e2 = 11, d2 = 12, c2 = 13, b2 = 14, a2 = 15,
  h3 = 16, g3 = 17, f3 = 18, e3 = 19, d3 = 20, c3 = 21, b3 = 22, a3 = 23,
  h4 = 24, g4 = 25, f4 = 26, e4 = 27, d4 = 28, c4 = 29, b4 = 30, a4 = 31,
  h5 = 32, g5 = 33, f5 = 34, e5 = 35, d5 = 36, c5 = 37, b5 = 38, a5 = 39,
  h6 = 40, g6 = 41, f6 = 42, e6 = 43, d6 = 44, c6 = 45, b6 = 46, a6 = 47,
  h7 = 48, g7 = 49, f7 = 50, e7 = 51, d7 = 52, c7 = 53, b7 = 54, a7 = 55,
  h8 = 56, g8 = 57, f8 = 58, e8 = 59, d8 = 60, c8 = 61, b8 = 62, a8 = 63
};

static const std::array<unsigned long long int, 64> binaryField = {
    0b0000000000000000000000000000000000000000000000000000000000000001,
    0b0000000000000000000000000000000000000000000000000000000000000010,
    0b0000000000000000000000000000000000000000000000000000000000000100,
    0b0000000000000000000000000000000000000000000000000000000000001000,
    0b0000000000000000000000000000000000000000000000000000000000010000,
    0b0000000000000000000000000000000000000000000000000000000000100000,
    0b0000000000000000000000000000000000000000000000000000000001000000,
    0b0000000000000000000000000000000000000000000000000000000010000000,
  
    0b0000000000000000000000000000000000000000000000000000000100000000,
    0b0000000000000000000000000000000000000000000000000000001000000000,
    0b0000000000000000000000000000000000000000000000000000010000000000,
    0b0000000000000000000000000000000000000000000000000000100000000000,
    0b0000000000000000000000000000000000000000000000000001000000000000,
    0b0000000000000000000000000000000000000000000000000010000000000000,
    0b0000000000000000000000000000000000000000000000000100000000000000,
    0b0000000000000000000000000000000000000000000000001000000000000000,

    0b0000000000000000000000000000000000000000000000010000000000000000,
    0b0000000000000000000000000000000000000000000000100000000000000000,
    0b0000000000000000000000000000000000000000000001000000000000000000,
    0b0000000000000000000000000000000000000000000010000000000000000000,
    0b0000000000000000000000000000000000000000000100000000000000000000,
    0b0000000000000000000000000000000000000000001000000000000000000000,
    0b0000000000000000000000000000000000000000010000000000000000000000,
    0b0000000000000000000000000000000000000000100000000000000000000000,

    0b0000000000000000000000000000000000000001000000000000000000000000,
    0b0000000000000000000000000000000000000010000000000000000000000000,
    0b0000000000000000000000000000000000000100000000000000000000000000,
    0b0000000000000000000000000000000000001000000000000000000000000000,
    0b0000000000000000000000000000000000010000000000000000000000000000,
    0b0000000000000000000000000000000000100000000000000000000000000000,
    0b0000000000000000000000000000000001000000000000000000000000000000,
    0b0000000000000000000000000000000010000000000000000000000000000000,

    0b0000000000000000000000000000000100000000000000000000000000000000,
    0b0000000000000000000000000000001000000000000000000000000000000000,
    0b0000000000000000000000000000010000000000000000000000000000000000,
    0b0000000000000000000000000000100000000000000000000000000000000000,
    0b0000000000000000000000000001000000000000000000000000000000000000,
    0b0000000000000000000000000010000000000000000000000000000000000000,
    0b0000000000000000000000000100000000000000000000000000000000000000,
    0b0000000000000000000000001000000000000000000000000000000000000000,

    0b0000000000000000000000010000000000000000000000000000000000000000,
    0b0000000000000000000000100000000000000000000000000000000000000000,
    0b0000000000000000000001000000000000000000000000000000000000000000,
    0b0000000000000000000010000000000000000000000000000000000000000000,
    0b0000000000000000000100000000000000000000000000000000000000000000,
    0b0000000000000000001000000000000000000000000000000000000000000000,
    0b0000000000000000010000000000000000000000000000000000000000000000,
    0b0000000000000000100000000000000000000000000000000000000000000000,

    0b0000000000000001000000000000000000000000000000000000000000000000,
    0b0000000000000010000000000000000000000000000000000000000000000000,
    0b0000000000000100000000000000000000000000000000000000000000000000,
    0b0000000000001000000000000000000000000000000000000000000000000000,
    0b0000000000010000000000000000000000000000000000000000000000000000,
    0b0000000000100000000000000000000000000000000000000000000000000000,
    0b0000000001000000000000000000000000000000000000000000000000000000,
    0b0000000010000000000000000000000000000000000000000000000000000000,

    0b0000000100000000000000000000000000000000000000000000000000000000,
    0b0000001000000000000000000000000000000000000000000000000000000000,
    0b0000010000000000000000000000000000000000000000000000000000000000,
    0b0000100000000000000000000000000000000000000000000000000000000000,
    0b0001000000000000000000000000000000000000000000000000000000000000,
    0b0010000000000000000000000000000000000000000000000000000000000000,
    0b0100000000000000000000000000000000000000000000000000000000000000,
    0b1000000000000000000000000000000000000000000000000000000000000000};
    
#endif
