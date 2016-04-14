#ifndef KNIGHT_H
#define KNIGHT_H
#include "Chessman.h"

class Knight :
  public Chessman
{
public:
  Knight(size_t _col, size_t _row, Color);

  virtual bool IsMovementAvailable(const Cell& _aim)const;
  virtual char GetTypeOfFigure()const;
};


#endif KNIGHT_H
