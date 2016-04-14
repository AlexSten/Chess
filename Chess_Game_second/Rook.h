#ifndef ROOK_H
#define ROOK_H
#include "Chessman.h"

class Rook :
  public Chessman
{
public:
  Rook(size_t _col, size_t _row, Color);

  virtual bool IsMovementAvailable(const Cell& _aim)const;
  virtual char GetTypeOfFigure()const;
};

#endif ROOK_H