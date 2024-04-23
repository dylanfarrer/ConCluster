#ifndef SINGLE_SERVERS_H
#define SINGLE_SERVERS_H

#include "address.h"

/**
 * @brief struct to represent a single 'server' and serve mechanism.
 * Takes an address struct as a member to represent the set of server addresses.
 * Possible use cases:
 *  1.
 *      node_address -> set of IP addresses to serve
 *      serve -> serve function
 *  2.
 *      node_address -> set of files to watch
 *      serve -> watch/act function
 *  3.
 *      node_address -> set of message bus channels
 *      serve -> subscribe function
 */
typedef struct {
    ccon_n_node_address* address;
    int invocation_status;
    void* (*serve) (void*);
} ccon_n_node_single_server;

/**
 * @brief Create a node_single_server struct.
 * Performs a shallow copy on the address struct.
 * if malloc fails, returns NULL.
 * 
 * @param address address struct to represent server addresses.
 * @param serve void* (void*) function pointer to represent a serve mechanism.
 * @return ccon_n_node_single_server* struct or NULL.
 */
ccon_n_node_single_server* ccon_n_create_single_server(ccon_n_node_address* address, void* (*serve) (void*));

/**
 * @brief performs deep copy on ccon_n_single_server struct to create new node_single_server.
 * if single_server is NULL, return NULL
 * 
 * @param single_server struct to copy
 * @return ccon_n_node_single_server* struct, or NULL
 */
ccon_n_node_single_server* ccon_n_copy_single_server(ccon_n_node_single_server* single_server);

/**
 * @brief deletes a ccon_n_node_single_server struct.
 * Calls address function to delete address member - if this fails, delete operation cancelled.
 * 
 * @param node_single_server struct to free.
 * @return int 0 on success, -1 on failure.
 */
int ccon_n_delete_single_server(ccon_n_node_single_server* single_server);

#endif
