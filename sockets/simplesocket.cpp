#include "simplesocket.h"
#include <WS2tcpip.h>
#include <cstdint>
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

// Constructor
bnet::SimpleSocket::SimpleSocket(int domain, int type, int protocol, int port, u_long ipAddress)
{
    // Define adress structure
    m_adress.sin_family = domain;
    m_adress.sin_port = htons(port);
    m_adress.sin_addr.s_addr = htonl(ipAddress);
    // Establish socket
    m_sock = socket(domain, type, protocol);
    // Establish network connection (binding)
    test_connection(m_sock);
}

// Test connection (it test if the socket is binded)
void bnet::SimpleSocket::test_connection(int connectionToTest)
{
    // Confirms that connection has been properly stablished
    if (connectionToTest < 0)
    {
        perror("Failed to connect");
        //std::cerr << "Failed to connect...";
        exit(EXIT_FAILURE);
    }
}

struct sockaddr_in bnet::SimpleSocket::get_address()
{
    return m_adress;
}

int bnet::SimpleSocket::get_sock()
{
    return m_sock;
}
