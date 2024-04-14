#include "../../include/node/servers.h"

#include <stdlib.h>
#include <memory.h>

node_servers* create_servers(node_single_server** servers, int server_count) {
    if (servers == NULL || server_count < 0) {
        return NULL;
    }

    for (int i = 0; i < server_count; i++) {
        if (servers[i] == NULL) {   
            return NULL;
        }
    }

    node_servers* servers_struct = malloc(sizeof(node_servers));
    if (servers_struct == NULL) {
        return NULL;
    }

    // plus one for null terminator
    servers_struct->servers = malloc(sizeof(node_single_server*) * (server_count + 1));
    if (servers_struct->servers == NULL) {
        free(servers_struct);
        return NULL;
    }

    for (int i = 0; i < server_count; i++) {
        servers_struct->servers[i] = servers[i];
    }

    // null terminate
    servers_struct->servers[server_count] = NULL;

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

    if (servers->servers != NULL) {
        for (int i = 0; i < servers->server_count; i++) {
            if (delete_single_server(servers->servers[i]) != 0) {
                return -1;
            }
        }
        free(servers->servers);
    }
    free(servers);
    return 0;
}
