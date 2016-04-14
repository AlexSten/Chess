#include "Knight.h"
#include "Cell.h"


Knight::Knight(size_t _column, size_t _row, Color _color) :Chessman(_column, _row, _color)
{
}

bool Knight::IsMovementAvailable(const Cell& _aim)const
{
  bool returnedValue = false;
  if (((GetVerOffset(_aim) + GetHorOffset(_aim) == 3)) && (GetVerOffset(_aim) >= 1) && (GetVerOffset(_aim) <= 2)) // ход буквой Г
    returnedValue = true;
  return returnedValue;
}

char Knight::GetTypeOfFigure()const
{
  return 'H';   // horse
}