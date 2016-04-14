#include "Cell.h"
#include <iostream>

Cell::Cell()
{}

Cell::Cell(const Cell& _copy)
{
  m_pos = _copy.m_pos;
  m_pChessman = _copy.m_pChessman;
}

Cell::~Cell()
{
  if (m_pChessman != nullptr)
    delete m_pChessman;
}

void Cell::RemoveFigure()
{
  m_pChessman = nullptr;
}

void Cell::DeleteFigure()
{
  m_pChessman->~Chessman();
  m_pChessman = nullptr;
}

void Cell::SetFigure(Chessman* _figure)
{
  m_pChessman = _figure;
}

Chessman* Cell::GetFigure()const
{
  return m_pChessman;
}

void Cell::SetPosition(size_t _column, size_t _row)
{
  m_pos.first = _column;
  m_pos.second = _row;
}

size_t Cell::GetColumn()const
{
  return m_pos.first;
}

size_t Cell::GetRow()const
{
  return m_pos.second;
}

bool  Cell::IsHasFigure()const
{
  bool returnedValue = false;
  if (m_pChessman != nullptr)
    returnedValue = true;
  return returnedValue;
}

bool Cell::IsMovementAvailable(const Cell& _aim)const
{
  return m_pChessman->IsMovementAvailable(_aim);
}

Color Cell::ColorOfFigure()const
{
  return m_pChessman->GetColor();
}
