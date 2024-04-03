#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

typedef char* (*FunctionPtr)();

int create_listener_socket(int port);

int listen_on_socket(int listener_socket,
                     char** endpoints,
                     FunctionPtr* functions,
                     int endpointCount);

int create_sender_socket();

char* send_and_recieve_on_socket(int sender_socket,
                                 const char* ip,
                                 int port,
                                 const char* message);

int send_kill_message(int sender_socket, const char* ip, int port);

#endif
