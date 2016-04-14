#ifndef KING_H
#define KING_H
#include "Chessman.h"

class King :
  public Chessman
{
public:
  King(size_t _col, size_t _row, Color);

  virtual bool IsMovementAvailable(const Cell& _aim)const;
  virtual char GetTypeOfFigure()const;
};

#endif KING_H