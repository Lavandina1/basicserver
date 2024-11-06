#pragma once

#include "bindingsocket.h"
#include <WS2tcpip.h>
#include <cstdint>
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

namespace bnet
{

class ListeningSocket : public BindingSocket
{
  private:
    int m_backlog;
    int m_listening;

  public:
    ListeningSocket(int domain, int type, int protocol, int port, u_long ipAddress, int backlog);
    void start_listening();
    void set_backlog(int backlog);
};

} // namespace bnet
