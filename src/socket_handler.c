#include "../include/socket_handler.h"

// TODO check if we need all of these
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>

#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024

// TODO: add error checking and early failure here
int create_listener_socket(int port) {
    int listenfd = 0;
	struct sockaddr_in serv_addr;

	char sendBuff[BUFFER_SIZE];

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);

	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	listen(listenfd, 10);

    return listenfd;
}

int listen_on_socket(int listener_socket,
                     char** endpoints,
                     FunctionPtr* functions,
                     int endpoint_count,
                     int functions_count) {
    return 0;
}

int create_sender_socket() {
    int sockfd = 0;
	char recvBuff[BUFFER_SIZE];
	memset(recvBuff, '0', sizeof(recvBuff));

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Error : Could not create socket \n");
		return 1;
	}
    return sockfd;
}

char* send_and_receive_on_socket(int sender_socket, const char* ip, int port, const char* message) {
    // Create socket address structure for the server
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    // Connect to the server
    if (connect(sender_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connect failed");
        return NULL;
    }

    // Send message to the server
    if (send(sender_socket, message, strlen(message), 0) < 0) {
        printf("Send failed");
        return NULL;
    }

    // Receive response from the server
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(sender_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0) {
        printf("Receive failed");
        return NULL;
    }

    // Null-terminate the received data
    buffer[bytes_received] = '\0';

    // Allocate memory for the received message
    char *received_message = malloc(strlen(buffer) + 1);
    if (received_message == NULL) {
        printf("Memory allocation failed");
        return NULL;
    }

    // Copy the received data to the allocated memory
    strcpy(received_message, buffer);

    // Close the socket
    close(sender_socket);

    // Return the received message
    return received_message;
}
