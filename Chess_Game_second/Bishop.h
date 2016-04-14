#ifndef BISHOP_H
#define BISHOP_H
#include "Chessman.h"

class Bishop :  public Chessman
{
public:
  Bishop(size_t _col, size_t _row, Color);

  virtual bool IsMovementAvailable(const Cell& _aim)const;
  virtual char GetTypeOfFigure()const;
};
#endif BISHOP_H
