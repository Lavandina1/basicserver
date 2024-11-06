#include "basicserver.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>

bnet::BasicServer::BasicServer(int domain, int type, int protocol, int port, u_long ipAddress, int backlog)
{
    socket = new ListeningSocket(domain, type, protocol, port, ipAddress, backlog);
}

void bnet::BasicServer::accepter()
{
    struct sockaddr_in address = socket->get_address();
    int addrlen = sizeof(address);

    //We accept the connection
    m_newSocket = accept(socket->get_sock(), reinterpret_cast<sockaddr*>(&address), static_cast<socklen_t*>(&addrlen));
    
    if (m_newSocket == INVALID_SOCKET){
        std::cout << "Could not connect to client socket\n";
    }

}

void bnet::BasicServer::handler()
{

    int noFlags {0}; //We hate magic numbers
    
    m_bytes = recv(m_newSocket, m_buffer, sizeof(m_buffer),noFlags);

    if (m_bytes < 0){
        std::cout << "Could not read client request \n";
    }


}

void bnet::BasicServer::responder()
{
    std::string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Lenght: ";

    

}

int bnet::BasicServer::get_newSocket()
{
    return m_newSocket;
}
