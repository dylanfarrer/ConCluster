#include "../../include/node/single_server.h"

#include <stdlib.h>
#include <memory.h>

node_single_server* create_single_server(node_address* address,
                                         void* (*serve) (void*)) {
    if (address == NULL) {
        return NULL;
    }

    node_single_server* single_server = malloc(sizeof(node_single_server));
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

int delete_single_server(node_single_server* single_server) {
    if (single_server == NULL) {
        return 0;
    }

    if (single_server->address != NULL) {
        // call address-specific function
        if (delete_address(single_server->address) != 0) {
            // if inner member delete failed, stop
            return -1;
        }
    }

    free(single_server);
    return 0;
}
