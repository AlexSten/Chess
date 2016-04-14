#ifndef QUEEN_H
#define QUEEN_H
#include "Chessman.h"
class Queen :
  public Chessman
{
public:
  Queen(size_t _col, size_t _row, Color);

  virtual bool IsMovementAvailable(const Cell& _aim)const;
  virtual char GetTypeOfFigure()const;
};
#endif QUEEN_H
