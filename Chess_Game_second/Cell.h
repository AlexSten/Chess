#ifndef CELL_H
#define CELL_H
#include "Chessman.h"

class Cell
{
private:
  Chessman* m_pChessman = nullptr;
  //first = column, second = row
  std::pair<size_t, size_t> m_pos;
public:
  Cell();
  Cell(const Cell& _copy);
  ~Cell();

  void RemoveFigure();
  void DeleteFigure();
  void SetFigure(Chessman*);
  Chessman* GetFigure()const;
  void SetPosition(size_t _col, size_t _row);

  size_t GetColumn()const;
  size_t GetRow()const;

  bool IsHasFigure()const;
  bool IsMovementAvailable(const Cell&)const;
  Color ColorOfFigure()const;
};
#endif CELL_H