#pragma once

#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>

namespace bnet
{

class BasicSocket
{
  private:
  SOCKET m_sock;

  public:
    // Constructor
    BasicSocket(int domain, int type, int protocol);
    
    // Test if the socket was created
    void test_socket(SOCKET socketToTest);

    int get_sock();
};

} // namespace bnet
