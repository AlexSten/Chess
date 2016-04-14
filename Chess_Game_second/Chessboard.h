#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Cell.h"
#include "Field.h"
#include "Display.h"

class Chessboard
{
private:
  Display m_fieldForDisp;
  Field m_field;
public:
  Chessboard();

  void SetUpAChessPosition();
  Chessman* TakeFigure(const std::pair<size_t, size_t>& _cellPos);
  bool PutFigure(const std::pair<size_t, size_t>& _cellPos, Chessman&); // возвращает true если убит король
  void DisplayYourself();
  void HideCursor()const;
  void SetAttributesForCell(const std::pair<size_t, size_t>& _cellPos, std::string _colorOfBackground = "default")const;

  size_t GetBoardWidth()const;
  size_t GetBoardHeight()const;
  Color GetFigureColor(const std::pair<size_t, size_t>& _cellPos)const;
  bool IsHasFigure(const std::pair<size_t, size_t>& _cellPos)const;
  bool IsMovementAvailable(const std::pair<size_t, size_t>&, const std::pair<size_t, size_t>&)const;
private:
  void DrawArrayForDisplay()const;
  void DrawUpperAndLowerBorders()const;
  void DrawLeftAndRightBorders()const;
  void DrawGameField()const;
  void DrawVerticalSymbols()const;
  void DrawHorizontalSymbols()const;
};

#endif CHESSBOARD_H