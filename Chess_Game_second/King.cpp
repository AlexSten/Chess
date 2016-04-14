#include "King.h"
#include "Cell.h"


King::King(size_t _column, size_t _row, Color _color) :Chessman(_column, _row, _color)
{
}

bool King::IsMovementAvailable(const Cell& _aim)const
{
  bool returnedValue = false;
  if ((GetHorOffset(_aim) <= 1) && (GetVerOffset(_aim) <= 1))   // ход возможен только на одну клетку, но в любом направлении
    returnedValue = true;
  return returnedValue;
}

char King::GetTypeOfFigure()const
{
  return 'K';
}