#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include <string_view>
#include <fstream>
#include "basicserver.h"

bnet::BasicServer::BasicServer(int domain, int type, int protocol, int port, std::string ipAddress, int backlog)
{
    socket = new ListeningSocket(domain, type, protocol, port, ipAddress, backlog);
}


//
std::string bnet::BasicServer::get_content_type(const std::string& fileName) {

    if (fileName.ends_with(".html")) return "text/html";
    if (fileName.ends_with(".js")) return "application/javascript";
    if (fileName.ends_with(".css")) return "text/css";
    if (fileName.ends_with(".png")) return "image/png";
    return "application/octet-stream";  // Default MIME type for unknown types
}

//We use this fuction to iterate the data from the requested file
std::string bnet::BasicServer::read_file(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cout << "File not found: " << filePath << std::endl;
        return "";
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}


//We parse data to know what file was requested by client
std::string bnet::BasicServer::parse_buffer(const std::string_view buffer)
{   
    std::string_view request(m_buffer);
    std::string fileName {};
    if (request.find("GET /") == 0) {
        size_t start = 5;  // Position after "GET /"
        size_t end = request.find(" ", start);
        fileName = request.substr(start, end - start);
    }
    if (fileName.empty() || fileName == "/") {
            fileName = "index.html"; // Default name
        }
return fileName;
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
    int noFlags{0};

    std::string requestedFile = parse_buffer(m_buffer);
    
    std::string responseBody = read_file(requestedFile);
    
    //If its empty we error out (404)
    if (responseBody.empty()) {
        responseBody = "<html><h1>404 Not Found</h1></html>";
        std::string notFoundResponse = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(responseBody.size()) + "\r\n\r\n" + responseBody;
        send(m_newSocket, notFoundResponse.c_str(), notFoundResponse.size(), noFlags);
        return;
    }
    
    // std::string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
    // std::string response = "<html><h1>Hello World<h1><html>";
    // serverMessage.append(std::to_string(response.size()));
    // serverMessage.append("\n\n");
    // serverMessage.append(response);
     
     std::string contentType = get_content_type(requestedFile);
     std::string serverMessage = "HTTP/1.1 200 OK\r\n " + contentType + "\r\nContent-Length: " + std::to_string(responseBody.size()) + "\r\n\r\n" + responseBody;

    int bytesSent{0};
    int totalBytesSent{0};
    //We iterate to make sure we send all the data
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

    bnet::BasicServer server (AF_INET, SOCK_STREAM, IPPROTO_TCP, 8080, "0.0.0.0", 10);
    server.launch();

    WSACleanup(); //This clean ups any open sockets left

    return 0;
}
