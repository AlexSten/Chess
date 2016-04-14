#include "Chessman.h"
#include "Cell.h"


Chessman::Chessman(size_t _column, size_t _row, Color _color) : m_pos(_column, _row), m_color(_color)
{
}

Chessman::~Chessman()
{
}

void Chessman::SetPosition(const std::pair<size_t, size_t>& _cellPos)
{
  m_pos = _cellPos;
}

Color Chessman::GetColor()const
{
  return m_color;
}

size_t Chessman::GetHorOffset(const Cell& _aim)const
{
  return (m_pos.first > _aim.GetColumn()) ? (m_pos.first - _aim.GetColumn()) : (_aim.GetColumn() - m_pos.first);
}

size_t Chessman::GetVerOffset(const Cell& _aim)const
{
  return (m_pos.second > _aim.GetRow()) ? (m_pos.second - _aim.GetRow()) : (_aim.GetRow() - m_pos.second);
}