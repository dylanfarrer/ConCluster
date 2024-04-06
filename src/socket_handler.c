#include "../include/socket_handler.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

static int create_listener_socket(int port);
static int create_sender_socket();
static void close_socket(int socket_fd);


int listen_on_socket(int port,
                     char** endpoints,
                     FunctionPtr* functions,
                     int endpoint_count,
                     int function_count) {
    
    if (endpoint_count != function_count) {
        printf("Endpoint count and function count do not match\n");
        return -1;
    }

    int listener_socket = create_listener_socket(port);
    if (listener_socket < 0) {
        return -1;
    }

    struct sockaddr_in client_addr;
    int client_socket;
    socklen_t client_addr_len = sizeof(client_addr);

    while (1) {
        // Accept incoming connections
        if ((client_socket = accept(listener_socket, (struct sockaddr*)&client_addr, &client_addr_len)) < 0) {
            printf("Accept failed\n");
            close_socket(listener_socket);
            continue;
        }

        // Read data from the client socket
        char buffer[BUFFER_SIZE];
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received < 0) {
            printf("Receive failed\n");
            close_socket(listener_socket);
            continue;
        }

        // Null-terminate the received data
        buffer[bytes_received] = '\0';

        if (strcmp(buffer, "KILL") == 0) {
            printf("Killing server...\n");
            close_socket(listener_socket);
            break;
        }

        // Compare the received data to the endpoints
        for (int i = 0; i < endpoint_count; i++) {
            if (endpoints[i] == NULL) {
                printf("Encountered NULL endpoint\n");
                close_socket(listener_socket);
                return -1;
            }
            if (strcmp(buffer, endpoints[i]) == 0) {
                const char* message = functions[i]();
                if (send(client_socket, message, strlen(message), 0) < 0) {
                    printf("Send failed\n");
                    close_socket(listener_socket);
                }
                break;
            }
        }
        const char* error_message = "ERR";
        if (send(client_socket, error_message, strlen(error_message), 0) < 0) {
            printf("Send failed\n");
            close_socket(listener_socket);
        }
    }
    return 0;
}

char* send_and_recieve_on_socket(const char* ip,
                                 int port,
                                 const char* message) {
    int sender_socket = create_sender_socket();
    if (sender_socket < 0) {
        return NULL;
    }

    // Create socket address structure for the server
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) != 1) {
        printf("Inet pton failed\n");
        close_socket(sender_socket);
        return NULL;
    }

    // Connect to the server
    if (connect(sender_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connect failed\n");
        close_socket(sender_socket);
        return NULL;
    }

    // Send message to the server
    if (send(sender_socket, message, strlen(message), 0) < 0) {
        printf("Send failed\n");
        close_socket(sender_socket);
        return NULL;
    }

    // Receive response from the server
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(sender_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0) {
        printf("Receive failed\n");
        close_socket(sender_socket);
        return NULL;
    }

    // Null-terminate the received data
    buffer[bytes_received] = '\0';

    char *received_message = malloc(strlen(buffer) + 1);
    if (received_message == NULL) {
        printf("Memory allocation failed\n");
        close_socket(sender_socket);
        return NULL;
    }

    strcpy(received_message, buffer);

    close_socket(sender_socket);
    return received_message;
}

int send_kill_message(const char* ip, int port) {
    int sender_socket = create_sender_socket();
    if (sender_socket < 0) {
        return -1;
    }

    char* message = "KILL";

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) != 1) {
        printf("Inet pton failed\n");
        close_socket(sender_socket);
        return -1;
    }

    // Connect to the server
    if (connect(sender_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connect failed\n");
        close_socket(sender_socket);
        return -1;
    }

    // Send message to the server
    if (send(sender_socket, message, strlen(message), 0) < 0) {
        printf("Send failed\n");
        close_socket(sender_socket);
        return -1;
    }

    close_socket(sender_socket);
    return 0;
}

static int create_listener_socket(int port) {
    int listenfd = 0;
	struct sockaddr_in serv_addr;

	char sendBuff[BUFFER_SIZE];

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_on_socket < 0) {
        printf("Could not create listener socket.\n");
        return -1;
    }
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Could not bind listener socket.\n");
        close_socket(listenfd);
        return -1;
    }

	if (listen(listenfd, 10) < 0) {
        printf("Could not mark socket as passive.\n");
        close_socket(listenfd);
        return -1;
    }

    return listenfd;
}

static int create_sender_socket() {
    int sockfd = 0;
	char recvBuff[BUFFER_SIZE];
	memset(recvBuff, '0', sizeof(recvBuff));

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Could not create sender socket.\n");
		return -1;
	}
    return sockfd;
}

static void close_socket(int socket_fd) {
    if (close(socket_fd) != 0) {
        if (errno == EBADF) {
            printf("Error: Bad file descriptor when closing socket.\n");
        } else if (errno == EINTR) {
            printf("Error: Interrupted system call when closing socket.\n");
        } else if (errno == EIO) {
            printf("Error: I/O error when closing socket.\n");
        } else {
            printf("Error: Unknown error when closing socket.\n");
        }
    }
}
