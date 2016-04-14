#ifndef INTERFACE_H
#define INTERFACE_H
#include <string>
#include "enums.h"

class Messages
{
private:
  std::wstring m_WhPlayer;
  std::wstring m_BlPlayer;
  Color m_CurrentPlayer;
public:
  Messages();

  void Acquaintance();
  void DisplayMessage(const MessageType& _type);
  void SetCurrentPlayer(const Color& _player);
  Color GetCurrentPlayer()const;
};

#endif INTERFACE_H