#ifndef CHESSMAN_H
#define CHESSMAN_H
#include "enums.h"
#include <iostream>

class Cell;

class Chessman
{
protected:
  Color m_color;
  //first = column, second = row
  std::pair<size_t, size_t> m_pos;
public:
  Chessman(size_t _col, size_t _row, Color);
  virtual ~Chessman();

  virtual void SetPosition(const std::pair<size_t, size_t>& _cellPos);
  Color GetColor()const;

  virtual bool IsMovementAvailable(const Cell& _aim)const = 0;
  virtual char GetTypeOfFigure()const = 0;
protected:
  virtual size_t GetHorOffset(const Cell& _aim)const;
  virtual size_t GetVerOffset(const Cell& _aim)const;
};
#endif CHESSMAN_H

