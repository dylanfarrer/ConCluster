#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024

typedef void (*FunctionPtr)();

int create_listener_socket();

int listen_on_socket(int listener,
           char** endpoints,
           FunctionPtr* functions,
           int endpointCount,
           int functionsCount);

int create_sender_socket();

char* send_and_recieve_on_socket(int sender, const char* message);

#endif
