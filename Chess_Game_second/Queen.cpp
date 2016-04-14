#include "Queen.h"
#include "Cell.h"


Queen::Queen(size_t _column, size_t _row, Color _color) :Chessman(_column, _row, _color)
{
}

bool Queen::IsMovementAvailable(const Cell& _aim)const
{
  bool returnedValue = false;

  if ((GetHorOffset(_aim) == 0) ^ (GetVerOffset(_aim) == 0))                 // �������� �� ����������� ��� ���������
    returnedValue = true;
  else if (GetHorOffset(_aim) == GetVerOffset(_aim))                         // �������� �� ���������
    returnedValue = true;

  return returnedValue;
}

char Queen::GetTypeOfFigure()const
{
  return 'Q';
}
