#pragma once

#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include "bindingsocket.h"

namespace bnet
{

class ListeningSocket : public BindingSocket
{
  private:
    int m_backlog;
    int m_listening;

  public:
    ListeningSocket(int domain, int type, int protocol, int port, std::string ipAddress, int backlog);
    void start_listening();
    void set_backlog(int backlog);
    void test_listening(int listening);
};

} // namespace bnet
