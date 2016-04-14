#include "Display.h"
#include "BoardSizes.h"
using namespace BoardSizes;


Display::Display() : m_ShiftDownForMessgeArea(1)
{
  m_ArrayForDisplay = new CHAR_INFO[ArraySize];
  PictureSettings(CountOfRows, RowSize);
  SetColors();
}

Display::~Display()
{
  delete[] m_ArrayForDisplay;
}

void Display::DisplayYourself()
{
  WriteConsoleOutput(
    m_hStdOut,
    m_ArrayForDisplay,
    m_size,
    m_coord,
    &m_sr);
}

void Display::HideCursor()const
{
  CONSOLE_CURSOR_INFO structCursorInfo;
  GetConsoleCursorInfo(m_hStdOut, &structCursorInfo);
  structCursorInfo.bVisible = false;
  SetConsoleCursorInfo(m_hStdOut, &structCursorInfo);
}

void Display::EraseSymbol(const size_t& _col, const size_t& _row)const
{
  size_t horizontalShift = (_col - 1) * CellSize + (CellSize / 2);
  size_t verticalShift = ((BoardHeight - _row) * CellSize + CellSize / 2) * RowSize;
  size_t borderShift = BorderWidth + BorderWidth * RowSize;
  m_ArrayForDisplay[horizontalShift + verticalShift + borderShift].Char.UnicodeChar = ' ';
}

void Display::SetAttributesForBlock(const size_t& _coordOfBlock, const std::string& _background, const wchar_t& _symbol)const
{
  m_ArrayForDisplay[_coordOfBlock].Char.UnicodeChar = _symbol;
  m_ArrayForDisplay[_coordOfBlock].Attributes = GetDesiredBackgroundColor(_background);
}

void Display::SetAttributesForBlock(const size_t& _coordOfBlock, const wchar_t& _symbol)const
{
  m_ArrayForDisplay[_coordOfBlock].Char.UnicodeChar = _symbol;
}

void Display::SetAttributesForCell(
  const size_t& _col
  , const size_t& _row
  , const std::string& _colorOfFigure
  , const char& _figureType
  , const std::string& _colorOfBackground
  )const
{
  for (size_t x = 0; x < CellSize; ++x)
  {
    for (size_t y = 0; y < CellSize; ++y)
    {
      size_t coordinateOfBlock = (_col - 1) * CellSize
        + (BoardHeight - _row)*CellSize*RowSize
        + RowSize * BorderWidth + BorderWidth
        + x + y * RowSize;

      WORD background = (_colorOfBackground == "default") ? (GetDefaultBackgroundForCell(_col, _row)) : (GetDesiredBackgroundColor(_colorOfBackground));
      m_ArrayForDisplay[coordinateOfBlock].Char.UnicodeChar = ' ';
      if (_colorOfFigure != "nothing")
        m_ArrayForDisplay[coordinateOfBlock].Attributes = background | GetForeground(_colorOfFigure);
      else
        m_ArrayForDisplay[coordinateOfBlock].Attributes = background;
    }
  }
  if (_figureType != ' ')
    m_ArrayForDisplay[GetCoordOfCentreOfCell(_col, _row)].Char.UnicodeChar = _figureType;
}

void Display::PictureSettings(const size_t& _countOfRows, const size_t& _rowSize)
{
  m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  m_coord.X = 0;
  m_coord.Y = 0;
  m_size.X = _rowSize;
  m_size.Y = _countOfRows;
  m_sr.Left = 0;
  m_sr.Top = m_ShiftDownForMessgeArea;
  m_sr.Right = _rowSize;
  m_sr.Bottom = _countOfRows;
}

void Display::SetColors()
{
  m_WhiteFigureColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
  m_BlackFigureColor = 0;
  m_BlackCellColor = BACKGROUND_GREEN | BACKGROUND_RED;
  m_WhiteCellColor = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
  m_ColorOfBordier = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE;
}

WORD Display::GetDefaultBackgroundForCell(const size_t& _col, const size_t& _row)const
{
  WORD color;
  if ((_col + _row) % 2 == 0)
    color = m_BlackCellColor;
  else
    color = m_WhiteCellColor;
  return color;
}

WORD Display::GetDesiredBackgroundColor(const std::string& _color)const
{
  WORD refundableBackground;
  if (_color == "white")
    refundableBackground = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
  else if (_color == "red")
    refundableBackground = BACKGROUND_RED | BACKGROUND_INTENSITY;
  else if (_color == "blue")
    refundableBackground = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
  else if (_color == "bordier")
    refundableBackground = m_ColorOfBordier;
  else 
    refundableBackground = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
  return refundableBackground;
}

WORD Display::GetForeground(const std::string& _colorOfFigure)const
{
  WORD foreground;
  if (_colorOfFigure == "white")
    foreground = m_WhiteFigureColor;
  else
    foreground = m_BlackFigureColor;
  return foreground;
}

size_t Display::GetCoordOfCentreOfCell(const size_t& _col, const size_t& _row)const
{
  return ((_col - 1) * CellSize
    + (BoardHeight - _row)*CellSize*RowSize
    + RowSize * BorderWidth + BorderWidth
    + CellSize / 2 + (CellSize / 2) * RowSize);
}
