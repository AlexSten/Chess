#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "Chessboard.h"
#include "Messages.h"


class Gamelogic
{
private:
  Messages m_mes;
  Chessboard m_CB;

  //first = column, second = row
  std::pair<size_t, size_t> m_SelectedCell;
  //first = column, second = row
  std::pair<size_t, size_t> m_AimCell;
  //first = column, second = row
  std::pair<size_t, size_t> m_ActiveCell;

  MessageType m_CurrentMessage;
  MessageType m_PreviousMessage;
  enum class direction
  {
    up,
    right,
    down,
    left
  };

  const size_t m_LightingTime = 1000;  //milliseconds
  bool m_fWin;
  bool m_fDisplayMessages;
public:
  Gamelogic();
  void Start();
private:
  void Movement();
  void Control();
  void ActiveCellsShift(const direction& _direction);
  void RelocateChessman();

  bool ChooseMovement();                              // когда задали клетку назначения, возвращает true
  void ChooseFigureForMovement();
  bool ChooseAimForMovement();                        // if wrong choise return false
  bool IsFigureSelected()const;

  bool PresenceOfFigure();
  bool IsOwnFigure();
  bool IsMovementAvailable();
  bool IsRouteAvailable();
  bool IsFreeWay()const;
  bool IsFreeWayHorizontal(const size_t& _horizontalOffset)const;
  bool IsFreeWayVertical(const size_t& _verticalOffset)const;
  bool IsFreeWayDiagonal(const size_t& _horizontalOffset)const;

  bool RightwardMovement()const;
  bool UpwardMovement()const;
  size_t RightwardShift()const;
  size_t LeftwardShift()const;
  size_t UpwardShift()const;
  size_t DownwardShift()const;

  void DisplayActiveCell(const std::string& _color);
  void RefreshScreen();
  bool IlluminationControl();           //return false if there are not available moves
  bool IlluminateAvailableMoves();                    //return false if there are not available moves
  void SetDefaultCollorSettingsForField();
  void SetCurrentMessage(const MessageType&);
  void Victory();
};

#endif GAMELOGIC_H