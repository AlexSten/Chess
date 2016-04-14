#ifndef DISPLAY_H
#define DISPLAY_H
#include <Windows.h>
#include <string>

class Display
{
  CHAR_INFO *m_ArrayForDisplay;

  HANDLE m_hStdOut;
  COORD m_size;
  COORD m_coord;
  SMALL_RECT m_sr;

  const size_t m_ShiftDownForMessgeArea;

  WORD m_BlackFigureColor;
  WORD m_WhiteFigureColor;
  WORD m_BlackCellColor;
  WORD m_WhiteCellColor;
  WORD m_ColorOfBordier;
public:
  Display();
  ~Display();

  void DisplayYourself();

  void HideCursor()const;
  void EraseSymbol(const size_t& _col, const size_t& _row)const;

  void SetAttributesForBlock(const size_t& _coordOfBlock, const std::string& _background, const wchar_t& _symbol)const;
  void SetAttributesForBlock(const size_t& _coordOfBlock, const wchar_t& _symbol)const;
  void SetAttributesForCell(
    const size_t& _col
    , const size_t& _row
    , const std::string& _colorOfFigure = "nothing"
    , const char& _figureType = ' '
    , const std::string& _colorOfBackground = "default"
    )const;
private:
  void PictureSettings(const size_t& _countOfRows, const size_t& _rowSize);
  void SetColors();

  WORD GetDefaultBackgroundForCell(const size_t& _col, const size_t& _row)const;
  WORD GetDesiredBackgroundColor(const std::string& _color)const;
  WORD GetForeground(const std::string& _colorOfFigure)const;
  size_t GetCoordOfCentreOfCell(const size_t& _col, const size_t& _row)const;
};
#endif DISPLAY_H
