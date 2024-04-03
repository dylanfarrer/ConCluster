#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

typedef void (*FunctionPtr)();

int create_listener_socket(int port);

int listen_on_socket(int listener,
           char** endpoints,
           FunctionPtr* functions,
           int endpointCount,
           int functionsCount);

int create_sender_socket();

char* send_and_recieve_on_socket(int sender,
                                 const char* ip,
                                 int port,
                                 const char* message);

#endif
