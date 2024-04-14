#include "../include/node.h"

#include <stdlib.h>

node* create_node(node_id* id,
                  node_role* role,
                  node_address* address,
                  node_actions* actions,
                  node_background_tasks* background_tasks,
                  node_servers* servers,
                  node_contacts* contacts) {
    if (id == NULL || \
        role == NULL || \
        address == NULL || \
        actions == NULL || \
        background_tasks == NULL || \
        servers == NULL || \
        contacts == NULL) {
        return NULL;
    }

    node* node_struct = malloc(sizeof(node));
    if (node_struct == NULL) {
        return NULL;
    }

    node_struct->id = id;
    node_struct->role = role;
    node_struct->address = address;
    node_struct->actions = actions;
    node_struct->background_tasks = background_tasks;
    node_struct->servers = servers;
    node_struct->contacts = contacts;

    return node_struct;
}

int delete_node(node* node) {
    if (node == NULL) {
        return 0;
    }

    if (delete_id(node->id) != 0) {
        return -1;
    }

    if (delete_role(node->role) != 0) {
        return -1;
    }

    if (delete_address(node->address) != 0) {
        return -1;
    }

    if (delete_actions(node->actions) != 0) {
        return -1;
    }

    if (delete_background_tasks(node->background_tasks) != 0) {
        return -1;
    }

    if (delete_servers(node->servers) != 0) {
        return -1;
    }

    if (delete_contacts(node->contacts) != 0) {
        return -1;
    }

    free(node);
    return 0;
}
