#include "Messages.h"
#include <iostream>

Messages::Messages()
{
  setlocale(LC_ALL, "rus_rus.866");
}

void Messages::Acquaintance()
{
  system("CLS");
  std::wcout << L"Введите имя Первого игрока и нажмите \"Enter\"." << std::endl;
  getline(std::wcin, m_WhPlayer);

  system("CLS");
  std::wcout << L"Введите имя Второго игрока и нажмите \"Enter\"." << std::endl;
  getline(std::wcin, m_BlPlayer);
}

void Messages::DisplayMessage(const MessageType& _type)
{
  (m_CurrentPlayer == Color::White) ? (std::wcout << m_WhPlayer) : (std::wcout << m_BlPlayer);

  switch (_type)
  {
  case MessageType::ChooseFigure:
    std::wcout << L", выбери фигуру: ";
    break;
  case MessageType::ChooseAim:
    std::wcout << L", ты выбрал фигуру, теперь реши, куда будешь ходить." << std::endl;
    break;
  case MessageType::WrongFigure:
    std::wcout << L", нельзя трогать чужие фигуры. ";
    std::wcout << L"Попробуй сделать другой ход: ";
    break;
  case MessageType::EmptyCell:
    std::wcout << L", ты не выбрал фигуру для хода. ";
    std::wcout << L"Попробуй еще раз: ";
    break;
  case MessageType::WrongCell:
    std::wcout << L", так ходить нельзя. ";
    std::wcout << L"Подумай и сделай правильный ход: ";
    break;
  case MessageType::UnavailableRoute:
    std::wcout << L", нельзя прыгать через фигуры. Сделай другой ход: ";
    break;
  case MessageType::HasNoAvailableMoves:
    std::wcout << L", Эта фигура не имеет достпуных ходов. Выбери другую фигуру: ";
    break;
  case MessageType::Congratulations:
    std::wcout << L", ты победил." << std::endl;
    break;
  case MessageType::Nothing:
    std::wcout << L"";
  default:
    break;
  }
}

void Messages::SetCurrentPlayer(const Color& _player)
{
  m_CurrentPlayer = _player;
}

Color Messages::GetCurrentPlayer()const
{
  return m_CurrentPlayer;
}