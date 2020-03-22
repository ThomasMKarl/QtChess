#ifndef PIECE_H
#define PIECE_H

#include <cstdlib>
#include <cmath>

class Piece
{
 public:
  virtual void movegen(){};
  virtual void move(){};
  
  unsigned short int get_pos() const
  {
    return log2(this->position);
  };

  void set_pos(unsigned short int pos)
  {
    position = pow(2,pos);
  };

  protected:
   unsigned long long int position;
   unsigned long long int moves;
   std::string color;
   bool ingame = true;
};
  
#endif
