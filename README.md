BasicServers, serves text files to clients, usually web-browsers, it's very modular and can be adapted to serve other types of clients.
This software has no security measures in place is just for testig.

Compiling advice:
This server is a Windows server, it won't work on other OS.
The server is compatible with C++23 standard, make sure your compiler is marked for C++23
*-std=c++23* flag on g++.
Make sure your compiler is also marked with *-lws2_32* flag, for proper linkage of Windows libreries.

Usage:
Just compile and start the server, it will serve files on the folder the app is started on, by request of the client usually a browser.
