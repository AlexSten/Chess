#include "Pawn.h"
#include "Cell.h"


Pawn::Pawn(size_t _column, size_t _row, Color _color) :Chessman(_column, _row, _color)
{
  m_IsFirstStep = true;
  m_CounterOfContacts = 0;
}

bool Pawn::IsMovementAvailable(const Cell& _aim)const
{
  bool returnedValue = false;
  if (IsAtack(_aim))
    returnedValue = AttackIsAllowed(_aim);
  else
    returnedValue = MovingIsAllowed(_aim);
  return returnedValue;
}

char Pawn::GetTypeOfFigure()const
{
  return 'P';
}

void Pawn::SetPosition(const std::pair<size_t, size_t>& _cellPos)
{
  m_pos = _cellPos;
  if (m_CounterOfContacts >= 1)
    m_IsFirstStep = false;

  ++m_CounterOfContacts;
}

bool Pawn::IsAtack(const Cell& _aim)const
{
  bool returnedValue = false;
  if (_aim.IsHasFigure())
    returnedValue = true;
  else
    returnedValue = false;
  return returnedValue;
}

bool Pawn::AttackIsAllowed(const Cell& _aim)const
{
  bool returnedValue = false;
  if (_aim.GetFigure()->GetColor() != m_color)             // ���� ������ ������ ������
  {
    if ((_aim.GetColumn() == m_pos.first - 1) || (_aim.GetColumn() == m_pos.first + 1)) // ���� �� ���������
    {
      if (_aim.GetRow() == ((m_color == Color::White) ? (m_pos.second + 1) : (m_pos.second - 1)))                      // �� ���� ������ ������
        returnedValue = true;
    }
  }
  return returnedValue;
}

bool Pawn::MovingIsAllowed(const Cell& _aim)const
{
  bool returnedValue = false;

  if (_aim.GetColumn() == m_pos.first)                                                            // ��� ������ �� ������
  {
    if (_aim.GetRow() == ((m_color == Color::White) ? (m_pos.second + 1) : (m_pos.second - 1)))                       // ����� ������ �� ������ ������
      returnedValue = true;
    if ((_aim.GetRow() == ((m_color == Color::White) ? (m_pos.second + 2) : (m_pos.second - 2)) && (m_IsFirstStep)))  // ������ ��� ����� �� ���
      returnedValue = true;
  }
  return returnedValue;
}