#include "Rook.h"
#include "Cell.h"

Rook::Rook(size_t _column, size_t _row, Color _color) :Chessman(_column, _row, _color)
{
}

bool Rook::IsMovementAvailable(const Cell& _aim)const
{
  bool returnedValue = false;
  if ((GetHorOffset(_aim) == 0) ^ (GetVerOffset(_aim) == 0))          // движение по горизонтали или вертикали
    returnedValue = true;
  return returnedValue;
}

char Rook::GetTypeOfFigure()const
{
  return 'R';
}