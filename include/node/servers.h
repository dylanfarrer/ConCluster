#ifndef SERVERS_H
#define SERVERS_H

#include "single_server.h"

typedef struct {
    node_single_server** servers;
    int server_count;
} node_servers;

node_servers* create_servers(node_single_server** servers, int server_count);
int delete_servers(node_servers* servers);

#endif