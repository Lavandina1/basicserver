BasicServers, serves text files to clients, usually web-browsers, it's very modular and can be adapted to serve other types of clients.
This software has no security measures in place is just for testig.

Compiling advice:
This server is a Windows server, it won't work on other OS.
Make sure your compiler is marked with *-lws2_32* flag, for proper linkage of Windows libreries.
