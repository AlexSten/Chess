#ifndef PAWN_H
#define PAWN_H
#include "Chessman.h"

class Pawn :
  public Chessman
{
private:
  bool m_IsFirstStep;
  size_t m_CounterOfContacts;
public:
  Pawn(size_t _col, size_t _row, Color);

  virtual bool IsMovementAvailable(const Cell& _aim)const;
  virtual void SetPosition(const std::pair<size_t, size_t>& _cellPos);
  virtual char GetTypeOfFigure()const;
private:
  bool IsAtack(const Cell& _aim)const;
  bool AttackIsAllowed(const Cell& _aim)const;
  bool MovingIsAllowed(const Cell& _aim)const;
};

#endif PAWN_H