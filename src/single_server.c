#include "include/single_server.h"

#include <stdlib.h>
#include <memory.h>

ccon_n_node_single_server* ccon_n_create_single_server(ccon_n_node_address* address,
                                                       void* (*serve) (void*)) {
    ccon_n_node_single_server* single_server = malloc(sizeof(ccon_n_node_single_server));
    if (single_server == NULL) {
        return NULL;
    }

    // shallow copy
    single_server->address = address;

    // 0 -> not invoked, 1 -> invoked
    single_server->invocation_status = 0;
    single_server->serve = serve;
    return single_server;
}

ccon_n_node_single_server* ccon_n_copy_single_server(ccon_n_node_single_server* single_server) {
    if (single_server == NULL) {
        return NULL;
    }

    return ccon_n_create_single_server(ccon_n_copy_address(single_server->address),
                                single_server->serve);
}

int ccon_n_delete_single_server(ccon_n_node_single_server** single_server) {
    if (single_server == NULL || (*single_server) == NULL) {
        return 0;
    }

    // call address-specific function
    if (ccon_n_delete_address(&((*single_server)->address)) != 0) {
        // if inner member delete failed, stop
        return -1;
    }

    free((*single_server));
    *single_server = NULL;
    return 0;
}

void* ccon_n_invoke_server(ccon_n_node_single_server* single_server,
                           int* result,
                           void* arguments) {
    if (result == NULL) {
        return NULL;
    }

    if (single_server == NULL || \
        single_server->serve == NULL) {
        *result = -1;
        return NULL;
    }

    *result = 0;
    single_server->invocation_status = 1;
    return single_server->serve(arguments);
}
