#ifndef SINGLE_SERVERS_H
#define SINGLE_SERVERS_H

#include "address.h"

typedef struct {
    node_address* address;
    int invocation_status;
    void* (*serve) (void*);
} node_single_server;

node_single_server* create_single_server(node_address* address, void* (*serve) (void*));
int delete_single_server(node_single_server* single_server);

#endif