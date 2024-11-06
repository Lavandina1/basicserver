#pragma once

#include "sockets/bnetsockets.h"
#include <winsock2.h>
#include <stdio.h>

namespace bnet
{

class BasicServer
{
  private:
    char m_buffer[30000]{}; //The buffer of data
    int m_newSocket; //We use it to store the result of the connection with the client
    int m_bytes; //It keeps tracks of bytes recieved
    void accepter();
    void handler();
    void responder();

  public:
    // Server doesn't inherits from socket so we use a pointer
    ListeningSocket *socket;

    BasicServer(int domain, int type, int protocol, int port, u_long ipAddress, int backlog);

    ~BasicServer()
    {   
        //destructor for our pointer
        delete socket;
        socket = nullptr;
    }

    void launch();

    int get_newSocket();


};

} // namespace bnet
