#ifndef SERVERS_H
#define SERVERS_H

#include "single_server.h"

/**
 * @brief struct to represent a set of 'servers'.
 * Takes an array of ccon_n_node_single_server structs.
 * Possible use cases:
 *  1.
 *      see single_server.h
 */
typedef struct {
    ccon_n_node_single_server** servers;
    int server_count;
} ccon_n_node_servers;

/**
 * @brief Create a ccon_n_node_servers struct.
 * Creates a new server array, but shallow copies each ccon_n_node_single_server structs.
 * if malloc fails or server_count < 0, returns NULL.
 * Accepts NULL array, but will not accept NULL array items in non-NULL array.
 * 
 * @param servers set of ccon_n_node_single_server structs to represent servers.
 * @param server_count number of servers, used in operations.
 * @return ccon_n_node_servers* struct or NULL.
 */
ccon_n_node_servers* ccon_n_create_servers(ccon_n_node_single_server** servers, int server_count);

/**
 * @brief performs deep copy on ccon_n_node_servers struct to create new node_servers.
 * if servers is NULL, return NULL
 * 
 * @param servers struct to copy
 * @return ccon_n_node_servers* struct, or NULL
 */
ccon_n_node_servers* ccon_n_copy_servers(ccon_n_node_servers* servers);

/**
 * @brief deletes a ccon_n_node_servers struct.
 * Calls ccon_n_node_single_server function to delete ccon_n_node_single_server member - 
 * if this fails, delete operation cancelled.
 * 
 * @param node_servers struct to free.
 * @return int 0 on success, -1 on failure.
 */
int ccon_n_delete_servers(ccon_n_node_servers* servers);

#endif
