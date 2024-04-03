#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

typedef char* (*FunctionPtr)();

int listen_on_socket(int port,
                     char** endpoints,
                     FunctionPtr* functions,
                     int endpointCount);

char* send_and_recieve_on_socket(const char* ip,
                                 int port,
                                 const char* message);

int send_kill_message(const char* ip, int port);

#endif
