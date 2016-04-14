#include "Messages.h"
#include <iostream>

Messages::Messages()
{
  setlocale(LC_ALL, "rus_rus.866");
}

void Messages::Acquaintance()
{
  system("CLS");
  std::wcout << L"������� ��� ������� ������ � ������� \"Enter\"." << std::endl;
  getline(std::wcin, m_WhPlayer);

  system("CLS");
  std::wcout << L"������� ��� ������� ������ � ������� \"Enter\"." << std::endl;
  getline(std::wcin, m_BlPlayer);
}

void Messages::DisplayMessage(const MessageType& _type)
{
  (m_CurrentPlayer == Color::White) ? (std::wcout << m_WhPlayer) : (std::wcout << m_BlPlayer);

  switch (_type)
  {
  case MessageType::ChooseFigure:
    std::wcout << L", ������ ������: ";
    break;
  case MessageType::ChooseAim:
    std::wcout << L", �� ������ ������, ������ ����, ���� ������ ������." << std::endl;
    break;
  case MessageType::WrongFigure:
    std::wcout << L", ������ ������� ����� ������. ";
    std::wcout << L"�������� ������� ������ ���: ";
    break;
  case MessageType::EmptyCell:
    std::wcout << L", �� �� ������ ������ ��� ����. ";
    std::wcout << L"�������� ��� ���: ";
    break;
  case MessageType::WrongCell:
    std::wcout << L", ��� ������ ������. ";
    std::wcout << L"������� � ������ ���������� ���: ";
    break;
  case MessageType::UnavailableRoute:
    std::wcout << L", ������ ������� ����� ������. ������ ������ ���: ";
    break;
  case MessageType::HasNoAvailableMoves:
    std::wcout << L", ��� ������ �� ����� ��������� �����. ������ ������ ������: ";
    break;
  case MessageType::Congratulations:
    std::wcout << L", �� �������." << std::endl;
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