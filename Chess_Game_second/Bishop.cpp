#include "Bishop.h"
#include "Cell.h"

Bishop::Bishop(size_t _column, size_t _row, Color _color) :Chessman(_column, _row, _color)
{
}

bool Bishop::IsMovementAvailable(const Cell& _aim)const
{
  bool returnedValue = false;
  if (GetHorOffset(_aim) == GetVerOffset(_aim))               // движение только по диагонали
    returnedValue = true;
  return returnedValue;
}

char Bishop::GetTypeOfFigure()const
{
  return 'B';
}