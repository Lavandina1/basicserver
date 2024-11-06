#include "listeningsocket.h"
#include <WS2tcpip.h>
#include <cstdint>
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

bnet::ListeningSocket::ListeningSocket(int domain, int type, int protocol, int port, u_long ipAddress, int backlog)
    : bnet::BindingSocket::BindingSocket(domain, type, protocol, port, ipAddress)
{
    set_backlog(backlog);
    start_listening();
    test_connection(m_listening);
}

void bnet::ListeningSocket::start_listening()
{
    m_listening = listen(get_sock(), m_backlog);
}

void bnet::ListeningSocket::set_backlog(int backlog)
{
    m_backlog = backlog;
}
