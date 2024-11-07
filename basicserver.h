#pragma once

#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include "sockets/bnetsockets.h"
namespace bnet
{

class BasicServer
{
  private:
    char m_buffer[30000]={0}; // The buffer of data
    int m_newSocket;        // We use it to store the result of the connection with the client
    void accepter();
    void handler();
    void responder();

  public:
    // Server doesn't inherits from socket so we use a pointer
    ListeningSocket *socket;

    BasicServer(int domain, int type, int protocol, int port, std::string ipAddress, int backlog);

    ~BasicServer()
    {
        // Destructor for our pointer
        delete socket;
        socket = nullptr;
    }

    void launch();

    int get_newSocket();
};

} // namespace bnet
