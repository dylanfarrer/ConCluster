#ifndef SERVERS_H
#define SERVERS_H

#include "single_server.h"

/**
 * @brief struct to represent a set of 'servers'.
 * Takes an array of node_single_server structs.
 * Possible use cases:
 *  1.
 *      see single_server.h
 */
typedef struct {
    node_single_server** servers;
    int server_count;
} node_servers;

/**
 * @brief Create a node_servers struct.
 * Creates a new server array, but shallow copies each node_single_server structs.
 * if malloc fails or servers is NULL or server_count < 0, returns NULL.
 * 
 * @param servers set of node_single_server structs to represent servers. Cannot be NULL.
 * @param server_count number of servers, used in operations.
 * @return node_servers* struct or NULL.
 */
node_servers* create_servers(node_single_server** servers, int server_count);

/**
 * @brief deletes a node_servers struct.
 * Calls single_server function to delete single_server member - if this fails, delete operation cancelled.
 * 
 * @param node_servers struct to free.
 * @return int 0 on success, -1 on failure.
 */
int delete_servers(node_servers* servers);

#endif
