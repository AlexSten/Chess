#ifndef ENUMS_H
#define ENUMS_H
enum class Color
{
  White,
  Black
};
enum class MessageType
{
  ChooseFigure,
  ChooseAim,
  WrongFigure,
  EmptyCell,
  WrongCell,
  UnavailableRoute,
  HasNoAvailableMoves,
  Congratulations,
  Nothing
};
#endif ENUMS_H