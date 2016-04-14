#include "Chessboard.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include"Queen.h"
#include "King.h"
#include "BoardSizes.h"
using namespace BoardSizes;
#define COLOR ((row == 1) ? (Color::White) : (Color::Black))


Chessboard::Chessboard()
{
  for (size_t i = 1; i <= BoardHeight; ++i)
  {
    for (size_t j = 1; j <= BoardWidth; ++j)
    {
      m_field(j, i).SetPosition(j, i);
    }    
  }

  DrawArrayForDisplay();
}

void Chessboard::SetUpAChessPosition()
{
  for (size_t i = 1; i <= BoardWidth; ++i)
  {
    Chessman *PawnW = new Pawn(2, i, Color::White);
    std::pair<size_t, size_t> pos(i, 2);
    PutFigure(pos, *PawnW);

    Chessman *PawnB = new Pawn(BoardHeight - 1, i, Color::Black);
    pos.first = i;
    pos.second = BoardHeight - 1;
    PutFigure(pos, *PawnB);
  }

  for (size_t row = 1; row <= BoardHeight; ++row)
  {
    if ((row == 1) || (row == BoardHeight))
    {
      for (size_t col = 1; col <= BoardWidth; ++col)
      {
        Chessman * pFig;
        switch (col)
        {
        case 1:
        {
                pFig = new Rook(row, col, COLOR);
                break;
        }
        case 2:
        {
                pFig = new Knight(row, col, COLOR);
                break;
        }
        case 3:
        {
                pFig = new Bishop(row, col, COLOR);
                break;
        }
        case 4:
        {
                pFig = new Queen(row, col, COLOR);
                break;
        }
        case 5:
        {
                pFig = new King(row, col, COLOR);
                break;
        }
        case 6:
        {
                pFig = new Bishop(row, col, COLOR);
                break;
        }
        case 7:
        {
                pFig = new Knight(row, col, COLOR);
                break;
        }
        case 8:
        {
                pFig = new Rook(row, col, COLOR);
                break;
        }
        default:
          pFig = new Rook(row, col, COLOR);
          break;
        }
        std::pair<size_t, size_t> pos(col, row);
        PutFigure(pos, *pFig);
      }
    }
  }
}

Chessman* Chessboard::TakeFigure(const std::pair<size_t, size_t>& _cellPos)
{
  Chessman * fig = m_field(_cellPos).GetFigure();
  m_field(_cellPos).RemoveFigure();
  m_fieldForDisp.EraseSymbol(_cellPos.first, _cellPos.second);
  return fig;
}

bool Chessboard::PutFigure(const std::pair<size_t, size_t>& _cellPos, Chessman& _fig)
{
  bool returnValue = false;

  if (m_field(_cellPos).IsHasFigure())
  {
    // Проверка на удаление короля с поля(победы)
    Chessman * pFig = m_field(_cellPos).GetFigure();
    King* pIsKing = dynamic_cast<King*>(pFig);
    if (pIsKing)
      returnValue = true;

    m_field(_cellPos).DeleteFigure();
  }

  m_field(_cellPos).SetFigure(&_fig);
  SetAttributesForCell(_cellPos);

  _fig.SetPosition(_cellPos);

  return returnValue;
}

void Chessboard::DisplayYourself()
{
  m_fieldForDisp.DisplayYourself();
}

void Chessboard::HideCursor()const
{
  m_fieldForDisp.HideCursor();
}

void Chessboard::SetAttributesForCell(const std::pair<size_t, size_t>& _cellPos, std::string _colorOfBackground)const
{
  std::string _colorOfFigure;
  char symbolOfFigure;
  if (m_field(_cellPos).IsHasFigure())
  {
    symbolOfFigure = m_field(_cellPos).GetFigure()->GetTypeOfFigure();
    (m_field(_cellPos).GetFigure()->GetColor() == Color::White) ? (_colorOfFigure = "white") : (_colorOfFigure = "black");
  }
  else
  {
    symbolOfFigure = ' ';
    _colorOfFigure = "nothing";
  }
  m_fieldForDisp.SetAttributesForCell(_cellPos.first, _cellPos.second, _colorOfFigure, symbolOfFigure, _colorOfBackground);
}

size_t Chessboard::GetBoardWidth()const
{
  return BoardWidth;
}

size_t Chessboard::GetBoardHeight()const
{
  return BoardHeight;
}

Color Chessboard::GetFigureColor(const std::pair<size_t, size_t>& _cellPos)const
{
  return m_field(_cellPos).ColorOfFigure();
}

bool Chessboard::IsHasFigure(const std::pair<size_t, size_t>& _cellPos)const
{
  return m_field(_cellPos).IsHasFigure();
}

bool Chessboard::IsMovementAvailable(const std::pair<size_t, size_t>& _activeCell, const std::pair<size_t, size_t>& _aimCell)const
{
  bool retrurnValue = false;

  if (!m_field(_aimCell).IsHasFigure())                                                                // есть ли клетка свободна 
    retrurnValue = m_field(_activeCell).IsMovementAvailable(m_field(_aimCell));
  else if (m_field(_activeCell).GetFigure()->GetColor() != m_field(_aimCell).GetFigure()->GetColor())  //или там враг
    retrurnValue = m_field(_activeCell).IsMovementAvailable(m_field(_aimCell));
  return retrurnValue;
}

void Chessboard::DrawArrayForDisplay()const
{
  DrawUpperAndLowerBorders();
  DrawLeftAndRightBorders();
  DrawGameField();
}

void Chessboard::DrawUpperAndLowerBorders()const
{
  for (size_t i = 0; i < RowSize * BorderWidth; ++i)
  {
    m_fieldForDisp.SetAttributesForBlock(i, "bordier", ' ');

    int j = i + RowSize * (BoardHeight * CellSize + BorderWidth);
    m_fieldForDisp.SetAttributesForBlock(j, "bordier", ' ');
  }

  DrawHorizontalSymbols();
}

void Chessboard::DrawLeftAndRightBorders()const
{
  for (size_t i = RowSize; i < RowSize * (BoardHeight * CellSize + BorderWidth); i += RowSize)
  {
    for (size_t j = 0; j < BorderWidth; ++j)
    {
      m_fieldForDisp.SetAttributesForBlock((i + j), "bordier", ' ');
      m_fieldForDisp.SetAttributesForBlock((i + RowSize - 1 - j), "bordier", ' ');
    }
  }

  DrawVerticalSymbols();
}

void Chessboard::DrawGameField()const
{
  for (size_t col = 1; col <= BoardWidth; ++col)
  {
    for (size_t row = 1; row <= BoardHeight; ++row)
    {
      std::pair<size_t, size_t> pos(col, row);
      SetAttributesForCell(pos);
    }
  }
}

void Chessboard::DrawVerticalSymbols()const
{
  int y0, y1;
  for (size_t i = BoardHeight; i >= 1; --i)
  {
    y0 = RowSize * ((BoardHeight - i) * CellSize + BorderWidth + CellSize / 2) + BorderWidth / 2;
    y1 = y0 + RowSize - BorderWidth;

    m_fieldForDisp.SetAttributesForBlock(y0, i + 48);
    m_fieldForDisp.SetAttributesForBlock(y1, i + 48);
  }
}

void Chessboard::DrawHorizontalSymbols()const
{
  for (size_t i = 0; i < BoardWidth; ++i)
  {
    int x0 = i * CellSize + CellSize / 2 + BorderWidth + (BorderWidth / 2) * RowSize;
    int x1 = x0 + RowSize * (BoardHeight * CellSize + BorderWidth);
    switch (i)
    {
    case 0:
      m_fieldForDisp.SetAttributesForBlock(x0, 'A');
      m_fieldForDisp.SetAttributesForBlock(x1, 'A');
      break;
    case 1:
      m_fieldForDisp.SetAttributesForBlock(x0, 'B');
      m_fieldForDisp.SetAttributesForBlock(x1, 'B');
      break;
    case 2:
      m_fieldForDisp.SetAttributesForBlock(x0, 'C');
      m_fieldForDisp.SetAttributesForBlock(x1, 'C');
      break;
    case 3:
      m_fieldForDisp.SetAttributesForBlock(x0, 'D');
      m_fieldForDisp.SetAttributesForBlock(x1, 'D');
      break;
    case 4:
      m_fieldForDisp.SetAttributesForBlock(x0, 'E');
      m_fieldForDisp.SetAttributesForBlock(x1, 'E');
      break;
    case 5:
      m_fieldForDisp.SetAttributesForBlock(x0, 'F');
      m_fieldForDisp.SetAttributesForBlock(x1, 'F');
      break;
    case 6:
      m_fieldForDisp.SetAttributesForBlock(x0, 'G');
      m_fieldForDisp.SetAttributesForBlock(x1, 'G');
      break;
    case 7:
      m_fieldForDisp.SetAttributesForBlock(x0, 'H');
      m_fieldForDisp.SetAttributesForBlock(x1, 'H');
      break;
    default:
      m_fieldForDisp.SetAttributesForBlock(x0, '*');
      m_fieldForDisp.SetAttributesForBlock(x1, '*');
      break;
    }
  }
}