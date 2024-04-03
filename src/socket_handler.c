#include "../include/socket_handler.h"
#include <stdio.h>
#include <stdlib.h>

int create_listener_socket() {
    return 0;
}

int listen_on_socket(int listener_socket,
                     char** endpoints,
                     FunctionPtr* functions,
                     int endpoint_count,
                     int functions_count) {
    return 0;
}

int create_sender_socket() {
    return 0;
}

char* send_and_receive_on_socket(int sender_socket, const char* message) {
    return NULL;
}
