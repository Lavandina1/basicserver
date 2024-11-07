#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include "bindingsocket.h"

// Constructor
bnet::BindingSocket::BindingSocket(int domain, int type, int protocol, int port, std::string ipAddress)
    : bnet::BasicSocket::BasicSocket(domain, type, protocol)
{

    // We convert prepare to convert the string into a valid type
    const char* ip = ipAddress.c_str();

    // Define adress structure
    m_address.sin_family = domain;
    m_address.sin_port = htons(port);
    m_address.sin_addr.s_addr = inet_addr(ip);

    // We bind the socket
    m_binding = bind(get_sock(), reinterpret_cast<sockaddr*>(&m_address), sizeof(m_address));
    test_binding(m_binding);
}


void bnet::BindingSocket::test_binding(int binding)
{
    if (binding != 0){
        std::cout << "Could not bind socket \n";
    }  else  std::cout << "Binding \n";
}


int bnet::BindingSocket::get_binding()
{
    return m_binding;
}


struct sockaddr_in bnet::BindingSocket::get_address()
{
    return m_address;
}
