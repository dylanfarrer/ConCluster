#ifndef SINGLE_SERVERS_H
#define SINGLE_SERVERS_H

#define EXPORT __attribute__((__visibility__("default")))

#include "address.h"

/**
 * @brief struct to represent a single 'server' and serve mechanism.
 * Takes a ccon_n_node_address struct as a member to represent the set of server addresses.
 * Possible use cases:
 *  1.
 *      ccon_n_node_address -> set of IP addresses to serve
 *      serve -> serve function
 *  2.
 *      ccon_n_node_address -> set of files to watch
 *      serve -> watch/act function
 *  3.
 *      ccon_n_node_address -> set of message bus channels
 *      serve -> subscribe function
 */
typedef struct {
    ccon_n_node_address* address;
    int invocation_status;
    void* (*serve) (void*);
} ccon_n_node_single_server;

/**
 * @brief Create a node_single_server struct.
 * Performs a shallow copy on the ccon_n_node_address struct.
 * if malloc fails, returns NULL.
 * 
 * @param address ccon_n_node_address struct to represent server addresses.
 * @param serve void* (void*) function pointer to represent a serve mechanism.
 * @return ccon_n_node_single_server* struct or NULL.
 */
EXPORT ccon_n_node_single_server* ccon_n_create_single_server(ccon_n_node_address* address, void* (*serve) (void*));

/**
 * @brief performs deep copy on ccon_n_single_server struct to create new node_single_server.
 * if single_server is NULL, return NULL
 * 
 * @param single_server struct to copy
 * @return ccon_n_node_single_server* struct, or NULL
 */
EXPORT ccon_n_node_single_server* ccon_n_copy_single_server(ccon_n_node_single_server* single_server);

/**
 * @brief deletes a ccon_n_node_single_server struct.
 * Calls ccon_n_node_address function to delete ccon_n_node_address member - if this fails, delete operation cancelled.
 * nullified single server struct pointer.
 * 
 * @param node_single_server struct to free.
 * @return int 0 on success, -1 on failure.
 */
EXPORT int ccon_n_delete_single_server(ccon_n_node_single_server** single_server);

/**
 * @brief invokes the serve function pointer in the ccon_n_node_single_server struct
 * result must be a valid pointer, otherwise NULL is returned.
 * result will be set to zero if the function is invoked,
 * but does not necessarily indicate successful function execution.
 * 
 * @param single_server struct to utilise
 * @param result must not be NULL, will be overwritten to 0 or -1.
 * @param arguments args to give to server
 * @return void* returns serve return value.
 */
EXPORT void* ccon_n_invoke_server(ccon_n_node_single_server* single_server,
                                  int* result,
                                  void* arguments);

#endif
