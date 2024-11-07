#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include "basicsocket.h"

// Constructor
bnet::BasicSocket::BasicSocket(int domain, int type, int protocol)
{
    // Bind socket to address
    m_sock = socket(domain, type, protocol);
    test_socket(m_sock);
}


void bnet::BasicSocket::test_socket(SOCKET socketToTest)
{
    if (socketToTest == INVALID_SOCKET)
    {
        std::cout << "Could not create socket \n";
    }  else  std::cout << "Creating \n";
}

int bnet::BasicSocket::get_sock()
{
    return m_sock;
}
