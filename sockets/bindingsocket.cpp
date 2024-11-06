#include "bindingsocket.h"
#include <WS2tcpip.h>
#include <cstdint>
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

// Constructor
bnet::BindingSocket::BindingSocket(int domain, int type, int protocol, int port, u_long ipAddress)
    : bnet::SimpleSocket::SimpleSocket(domain, type, protocol, port, ipAddress)
{
    m_binding = connect_to_network(get_sock(), get_address());
    test_connection(m_binding);
}

// Definition of connect_to_network virtual function
int bnet::BindingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
    return bind(sock, reinterpret_cast<sockaddr*>(&address), sizeof(address));
}

int bnet::BindingSocket::get_binding()
{
    return m_binding;
}
