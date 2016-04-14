#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include "Cell.h"

class Field
{
private:
  std::vector<std::vector<Cell>> m_Field;
public:
  Field();
  Cell& operator () (const size_t& _col, const size_t& _row);
  const Cell& operator () (const size_t& _col, const size_t& _row)const;
  Cell& operator () (const std::pair<size_t, size_t>& _cell);
  const Cell& operator () (const std::pair<size_t, size_t>& _cell)const;
};


#endif FIELD_H