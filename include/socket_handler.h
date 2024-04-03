#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

/**
 * @brief Utility typedef for defining a function pointer array.
 * 
 */
typedef char* (*FunctionPtr)();

/**
 * @brief Attempt to create a new socket (AF_INET, SOCKSTREAM) and enter a continual loop listening for connections.
 *        Socket is closed on exit.
 * 
 * @param port port to listen on
 * @param endpoints array of endpoints this socket should serve.
 * @param functions array of functions the socket should call for each endpoint, should map one-to-one with endpoints.
 * @param endpointCount size of endpoints. Should equal function_count.
 * @param function_count size of functions. Should equal endpoint_count.
 * @return int 0 successfully killed server, -1 on error.
 */
int listen_on_socket(int port,
                     char** endpoints,
                     FunctionPtr* functions,
                     int endpointCount,
                     int function_count);

/**
 * @brief Attempt to create a new socket (AF_INET, SOCK_STREAM) and connect to the specified IP and port, send a message and recieve a response.
 *        Socket is closed on exit.
 * 
 * @param ip ip to connect to.
 * @param port port to connect to.
 * @param message message to send, upper limit of 1024 chars.
 * @return char* returned response or NULL upon error.
 */
char* send_and_recieve_on_socket(const char* ip,
                                 int port,
                                 const char* message);

/**
 * @brief Attempt to create a new socket (AF_INET, SOCK_STREAM) and connect to the specified IP and port, then send a kill message.
 *        Only compatible with servering sockets from this hader. Socket is closed on exit.
 * 
 * @param ip ip to connect to.
 * @param port port to connect to.
 * @return int 0 success, -1 on error.
 */
int send_kill_message(const char* ip, int port);

#endif
