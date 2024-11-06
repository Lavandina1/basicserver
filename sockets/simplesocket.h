#pragma once

#include <WS2tcpip.h>
#include <cstdint>
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

namespace bnet
{

class SimpleSocket
{
  private:
    struct sockaddr_in m_adress;
    int m_sock;
    int m_connection;

  public:
    // Constructor
    SimpleSocket(int domain, int type, int protocol, int port, u_long ipAddress);
    // Virtual function to connect to a network (socket binding)
    virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;

    // Test if the socket connection
    void test_connection(int connectionToTest);
    // Getters
    struct sockaddr_in get_address();
    int get_sock();
};

} // namespace bnet
