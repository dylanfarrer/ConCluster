#include "../../include/node/servers.h"

#include <stdlib.h>
#include <memory.h>

node_servers* create_servers(node_single_server** servers, int server_count) {
    if (server_count < 0) {
        return NULL;
    }

    node_servers* servers_struct = malloc(sizeof(node_servers));
    if (servers_struct == NULL) {
        return NULL;
    }

    if (servers == NULL) {
        servers_struct->servers = NULL;
        servers_struct->server_count = 0;
        return servers_struct;
    }

    // although pointer array length cannot directly be determined,
    // if count is less than one, it is not representative of the array.
    if (server_count < 1) {
        free(servers_struct);
        return NULL;
    }

    // if there is a null member in the array, return NULL.
    for (int i = 0; i < server_count; i++) {
        if (servers[i] == NULL) {  
            free(servers_struct); 
            return NULL;
        }
    }

    servers_struct->servers = malloc(sizeof(node_single_server*) * server_count);
    if (servers_struct->servers == NULL) {
        free(servers_struct);
        return NULL;
    }

    for (int i = 0; i < server_count; i++) {
        servers_struct->servers[i] = servers[i];
    }

    servers_struct->server_count = server_count;
    return servers_struct;
}

int delete_servers(node_servers* servers) {
    if (servers == NULL) {
        return 0;
    }

    if (servers->server_count < 0) {
        return -1;
    }

    for (int i = 0; i < servers->server_count; i++) {
        if (delete_single_server(servers->servers[i]) != 0) {
            return -1;
        }
    }
    free(servers->servers);

    free(servers);
    return 0;
}
