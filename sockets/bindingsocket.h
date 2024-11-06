#pragma once

#include "simplesocket.h"
#include <WS2tcpip.h>
#include <cstdint>
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

namespace bnet
{

class BindingSocket : public SimpleSocket
{
  private: 
  int m_binding;

  public:
    // Constructor
    BindingSocket(int domain, int type, int protocol, int port, u_long ipAddress);

    // Virtual function from parent
    int connect_to_network(int sock, struct sockaddr_in address);

    int get_binding();
};

} // namespace bnet
