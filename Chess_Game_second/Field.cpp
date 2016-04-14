#include "Field.h"
#include "BoardSizes.h"
using BoardSizes::BoardWidth;
using BoardSizes::BoardHeight;

Field::Field() : m_Field(BoardWidth, std::vector<Cell>(BoardHeight))
{
}

Cell& Field::operator() (const size_t& _col, const size_t& _row)
{
  return m_Field[_col - 1][_row - 1];
}

const Cell& Field::operator() (const size_t& _col, const size_t& _row)const
{
  return m_Field[_col - 1][_row - 1];
}

Cell& Field::operator () (const std::pair<size_t, size_t>& _cell)
{
  return m_Field[_cell.first - 1][_cell.second - 1];
}

const Cell& Field::operator () (const std::pair<size_t, size_t>& _cell)const
{
  return m_Field[_cell.first - 1][_cell.second - 1];
}