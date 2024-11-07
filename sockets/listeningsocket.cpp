#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include "listeningsocket.h"


bnet::ListeningSocket::ListeningSocket(int domain, int type, int protocol, int port, std::string ipAddress, int backlog)
    : bnet::BindingSocket::BindingSocket(domain, type, protocol, port, ipAddress)
{
    set_backlog(backlog);
    m_listening = listen(get_sock(), m_backlog);
    test_listening(m_listening);
}

void bnet::ListeningSocket::test_listening(int listening)
{
    if (listening != 0){
        std::cout << "Could not start listening \n";
    }
    else  std::cout << "Listening \n";
}

void bnet::ListeningSocket::start_listening()
{
    m_listening = listen(get_sock(), m_backlog);
}

void bnet::ListeningSocket::set_backlog(int backlog)
{
    m_backlog = backlog;
}
