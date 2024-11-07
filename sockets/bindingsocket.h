#pragma once

#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include "basicsocket.h"

namespace bnet
{

class BindingSocket : public BasicSocket
{
  private: 
  int m_binding;
  struct sockaddr_in m_address;

  public:
    // Constructor
    BindingSocket(int domain, int type, int protocol, int port, std::string ipAddress);



    //int connect_to_network(int sock, struct sockaddr_in address);

    void test_binding(int binding);

    int get_binding();
    struct sockaddr_in get_address();
};

} // namespace bnet
