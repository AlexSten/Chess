#include "Gamelogic.h"
#include "Chessboard.h"
#include "King.h"

Gamelogic::Gamelogic()
{
  m_mes.SetCurrentPlayer(Color::White);
  m_CB.SetUpAChessPosition();
  m_fWin = false;
  m_ActiveCell = std::make_pair(1, 1);
  m_fDisplayMessages = true;
  m_CurrentMessage = MessageType::Nothing;
  m_PreviousMessage = MessageType::Nothing;
}

void Gamelogic::Start()
{
  m_mes.Acquaintance();
  m_CB.HideCursor();

  while (!m_fWin)
  {
    Movement();
    if (!m_fWin)
    {
      (m_mes.GetCurrentPlayer() == Color::White) ? (m_mes.SetCurrentPlayer(Color::Black)) : (m_mes.SetCurrentPlayer(Color::White));
      m_AimCell = std::make_pair(0, 0); m_SelectedCell = std::make_pair(0, 0);
    }
  }
  Victory();
}

void Gamelogic::Movement()
{
  RefreshScreen();
  Control();
  RelocateChessman();
}

void Gamelogic::Control()
{
  DisplayActiveCell("white");
  SetCurrentMessage(MessageType::ChooseFigure);
  RefreshScreen();
  bool isMovementChosen = false;
  while (!isMovementChosen)
  {
    if (GetAsyncKeyState(VK_UP))
    {
      keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
      if (m_ActiveCell.second < m_CB.GetBoardHeight())
        ActiveCellsShift(direction::up);
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
      keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
      if (m_ActiveCell.second > 1)
        ActiveCellsShift(direction::down);
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
      keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
      if (m_ActiveCell.first > 1)
        ActiveCellsShift(direction::left);
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
      keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
      if (m_ActiveCell.first < m_CB.GetBoardWidth())
        ActiveCellsShift(direction::right);
    }
    if (GetAsyncKeyState(VK_LSHIFT))
    {
      keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
      if (m_SelectedCell.first != 0)
        IlluminationControl();
    }
    if (GetAsyncKeyState(VK_SPACE))
    {
      keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
      isMovementChosen = ChooseMovement();
      RefreshScreen();
    }
  }
}

void Gamelogic::ActiveCellsShift(const direction& _direction)
{
  DisplayActiveCell("default");
  switch (_direction)
  {
  case direction::up:
    m_ActiveCell.second += 1;
    break;
  case direction::right:
    m_ActiveCell.first += 1;
    break;
  case direction::down:
    m_ActiveCell.second -= 1;
    break;
  case direction::left:
    m_ActiveCell.first -= 1;
    break;
  default:
    break;
  }
  DisplayActiveCell("white");
  (IsFigureSelected()) ? (SetCurrentMessage(MessageType::ChooseFigure)) : (SetCurrentMessage(MessageType::ChooseAim));
  RefreshScreen();
}

void Gamelogic::RelocateChessman()
{
  Chessman * pFig = m_CB.TakeFigure(m_SelectedCell);
  m_fWin = m_CB.PutFigure(m_AimCell, *pFig);
}

bool Gamelogic::ChooseMovement()
{
  bool returnedValue = false;
  if (IsFigureSelected())
    ChooseFigureForMovement();
  else
    returnedValue = ChooseAimForMovement();
  return returnedValue;
}

void Gamelogic::ChooseFigureForMovement()
{
  m_SelectedCell = m_ActiveCell;

  if (!PresenceOfFigure() || !IsOwnFigure() || !IlluminationControl())
    m_SelectedCell = std::make_pair(0, 0);
}

bool Gamelogic::ChooseAimForMovement()
{
  m_AimCell = m_ActiveCell;
  bool returnedValue = false;

  if (!IsMovementAvailable() || !IsRouteAvailable())
    m_AimCell = std::make_pair(0, 0);
  else
    returnedValue = true;
  return returnedValue;
}

bool Gamelogic::IsFigureSelected()const
{
  return m_SelectedCell.first == 0;
}

bool Gamelogic::PresenceOfFigure()
{
  bool returnedValue = true;
  if (!m_CB.IsHasFigure(m_SelectedCell))
  {
    if (m_fDisplayMessages)
      SetCurrentMessage(MessageType::EmptyCell);
    returnedValue = false;
  }
  return returnedValue;
}

bool Gamelogic::IsOwnFigure()
{
  bool returnedValue = true;
  if (m_CB.GetFigureColor(m_SelectedCell) != m_mes.GetCurrentPlayer())
  {
    if (m_fDisplayMessages)
      SetCurrentMessage(MessageType::WrongFigure);
    returnedValue = false;
  }
  return returnedValue;
}

bool Gamelogic::IsMovementAvailable()
{
  bool returnedValue = true;
  if (!m_CB.IsMovementAvailable(m_SelectedCell, m_AimCell))
  {
    if (m_fDisplayMessages)
      SetCurrentMessage(MessageType::WrongCell);
    returnedValue = false;
  }
  return returnedValue;
}

bool Gamelogic::IsRouteAvailable()
{
  bool returnedValue = true;
  if (!IsFreeWay())
  {
    if (m_fDisplayMessages)
      SetCurrentMessage(MessageType::UnavailableRoute);
    returnedValue = false;
  }
  return returnedValue;
}

bool Gamelogic::IsFreeWay()const
{
  bool returnedValue = false;
  int horizontalOffset = RightwardMovement() ? RightwardShift() : LeftwardShift();
  int verticalOffset = UpwardMovement() ? UpwardShift() : DownwardShift();

  if (verticalOffset == 0)
  {
    returnedValue = IsFreeWayHorizontal(horizontalOffset);
  }
  else if (horizontalOffset == 0)
  {
    returnedValue = IsFreeWayVertical(verticalOffset);
  }
  else if (horizontalOffset == verticalOffset)
  {
    returnedValue = IsFreeWayDiagonal(horizontalOffset);
  }
  else if ((horizontalOffset + verticalOffset) == 3)             // если это ход коня, то он перепрыгивает и путь всегда свободен
    returnedValue = true;
  return returnedValue;
}

bool Gamelogic::IsFreeWayHorizontal(const size_t& _horizontalOffset)const
{
  size_t row = m_AimCell.second;
  size_t col = m_SelectedCell.first;
  bool returnedValue = true;

  for (size_t i = 1; i < _horizontalOffset; ++i)
  {
    if (RightwardMovement())
      ++col;
    else
      --col;
    std::pair<size_t, size_t> pos(col, row);
    if (m_CB.IsHasFigure(pos))
      returnedValue = false;
  }
  return returnedValue;
}

bool Gamelogic::IsFreeWayVertical(const size_t& _verticalOffset)const
{
  size_t row;
  size_t col = m_AimCell.first;
  bool returnedValue = true;

  for (size_t i = 1; i < _verticalOffset; ++i)
  {
    if (UpwardMovement())
      row = m_SelectedCell.second + i;
    else
      row = m_SelectedCell.second - i;

    std::pair<size_t, size_t> pos(col, row);
    if (m_CB.IsHasFigure(pos))
      returnedValue = false;
  }
  return returnedValue;
}

bool Gamelogic::IsFreeWayDiagonal(const size_t& _horizontalOffset)const
{
  size_t col = m_SelectedCell.first;
  size_t row;
  bool returnedValue = true;

  for (size_t i = 1; i < _horizontalOffset; ++i)
  {
    if (RightwardMovement())
      ++col;
    else
      --col;

    if (UpwardMovement())
      row = m_SelectedCell.second + i;
    else
      row = m_SelectedCell.second - i;

    std::pair<size_t, size_t> pos(col, row);
    if (m_CB.IsHasFigure(pos))
      returnedValue = false;
  }
  return returnedValue;
}

bool Gamelogic::RightwardMovement()const
{
  return m_SelectedCell.first < m_AimCell.first;
}

bool Gamelogic::UpwardMovement()const
{
  return m_SelectedCell.second < m_AimCell.second;
}

size_t Gamelogic::RightwardShift()const
{
  return m_AimCell.first - m_SelectedCell.first;
}

size_t Gamelogic::LeftwardShift()const
{
  return m_SelectedCell.first - m_AimCell.first;
}

size_t Gamelogic::UpwardShift()const
{
  return m_AimCell.second - m_SelectedCell.second;
}

size_t Gamelogic::DownwardShift()const
{
  return m_SelectedCell.second - m_AimCell.second;
}

void Gamelogic::DisplayActiveCell(const std::string& _color)
{
  m_CB.SetAttributesForCell(m_ActiveCell, _color);
}

void Gamelogic::RefreshScreen()
{
  if (m_CurrentMessage != m_PreviousMessage)
  {
    system("cls");
    m_mes.DisplayMessage(m_CurrentMessage);
  }
  m_CB.DisplayYourself();
}

bool Gamelogic::IlluminationControl()
{
  m_fDisplayMessages = false;
  DisplayActiveCell("default");

  bool currentFigureCanMove = IlluminateAvailableMoves();

  if (currentFigureCanMove)
  {
    SetCurrentMessage(MessageType::ChooseAim);
    RefreshScreen();
    Sleep(m_LightingTime);
    SetDefaultCollorSettingsForField();
    DisplayActiveCell("white");
    RefreshScreen();
  }
  else
  {
    DisplayActiveCell("white");
    SetCurrentMessage(MessageType::HasNoAvailableMoves);
    m_SelectedCell = std::make_pair(0, 0);
  }

  m_AimCell = std::make_pair(0, 0);
  m_fDisplayMessages = true;

  return currentFigureCanMove;
}

bool Gamelogic::IlluminateAvailableMoves()
{
  bool isHaveSuchMoves = false;
  for (size_t col = 1; col <= m_CB.GetBoardWidth(); ++col)
  {
    for (size_t row = 1; row <= m_CB.GetBoardHeight(); ++row)
    {
      m_AimCell = std::make_pair(col, row);
      if (IsMovementAvailable() && IsRouteAvailable())
      {
        std::pair<size_t, size_t> pos(col, row);
        m_CB.SetAttributesForCell(pos, "white");
        isHaveSuchMoves = true;
      }
    }
  }
  return isHaveSuchMoves;
}

void Gamelogic::SetDefaultCollorSettingsForField()
{
  for (size_t col = 1; col <= m_CB.GetBoardWidth(); ++col)
  {
    for (size_t row = 1; row <= m_CB.GetBoardHeight(); ++row)
    {
      std::pair<size_t, size_t> pos(col, row);
      m_CB.SetAttributesForCell(pos, "default");
    }
  }
}

void Gamelogic::SetCurrentMessage(const MessageType& _type)
{
  m_PreviousMessage = m_CurrentMessage;
  m_CurrentMessage = _type;
}

void Gamelogic::Victory()
{
  SetCurrentMessage(MessageType::Congratulations);
  RefreshScreen();
  Sleep(m_LightingTime);
}