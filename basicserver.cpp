#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include "basicserver.h"

bnet::BasicServer::BasicServer(int domain, int type, int protocol, int port, std::string ipAddress, int backlog)
{
    socket = new ListeningSocket(domain, type, protocol, port, ipAddress, backlog);
    launch();
}

void bnet::BasicServer::accepter()
{ 
    struct sockaddr_in address = socket->get_address();
    int addrlen = sizeof(address);

    // We accept the connection from client this will create a new socket
m_newSocket = accept(socket->get_sock(), reinterpret_cast<sockaddr *>(&address), static_cast<socklen_t *>(&addrlen));
        
    //m_newSocket = accept(socket->get_sock(), (struct sockaddr*)&address, (socklen_t*)&addrlen);

    if (m_newSocket == INVALID_SOCKET)
    {
        std::cout << "Could not connect to client socket\n";
    }
}

void bnet::BasicServer::handler()
{
    // This function handle the client request

    int noFlags{0}; // We hate magic numbers
    int bytesRecived = recv(m_newSocket, m_buffer, sizeof(m_buffer), noFlags);
    
    if (bytesRecived < 0)
    {
        std::cout << "Could not read client request \n";
    }
    std::cout << m_buffer << std::endl;
}

void bnet::BasicServer::responder()
{

    std::string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
    std::string response = "<html><h1>Hello World<h1><html>";
    serverMessage.append(std::to_string(response.size()));
    serverMessage.append("\n\n");
    serverMessage.append(response);
    
    int bytesSent{0};
    int totalBytesSent{0};
    int noFlags{0};

    while (totalBytesSent < serverMessage.size()){

        //We send the data to our client
        bytesSent = send(m_newSocket,serverMessage.c_str(), serverMessage.size(), noFlags);
        if (bytesSent < 0){
            std::cout << "Could not send response \n";
        }
        
        totalBytesSent += bytesSent;
    }
    std::cout << "Response sent to client \n";
    //closesocket(m_newSocket);*/
}


void bnet::BasicServer::launch()
{
    //Here we iniciate the main loop.

    while (true)
    {
        std::cout << "===== WAITING =====" << std::endl;
        accepter();
        handler();
        responder();
        std::cout << "===== DONE =====" << std::endl;
        closesocket(m_newSocket);
    }
}


int bnet::BasicServer::get_newSocket()
{
    return m_newSocket;
}

int main()
{
    WSADATA wsaDATA; //This is required by the WSAStartup function to keep an internal registry of open sockets

    std::cout << "Attempting to create a server \n";

    //We must start this fuction in order to work with the Windows libreries
    if(WSAStartup(MAKEWORD(2,2), &wsaDATA) !=0){
        std::cout << "Could not initialize \n";
    }

    bnet::BasicServer server (AF_INET, SOCK_STREAM, 0, 8080, "0.0.0.0", 10);

    WSACleanup(); //This clean ups any open sockets left

    return 0;
}
