#include "../include/node.h"

#include <stdlib.h>
#include <stdio.h>

ccon_node* ccon_create_node(ccon_n_node_id* id,
                            ccon_n_node_role* role,
                            ccon_n_node_address* address,
                            ccon_n_node_actions* actions,
                            ccon_n_node_background_tasks* background_tasks,
                            ccon_n_node_servers* servers,
                            ccon_n_node_contacts* contacts) {
    if (id == NULL || \
        role == NULL || \
        address == NULL || \
        actions == NULL || \
        background_tasks == NULL || \
        servers == NULL || \
        contacts == NULL) {
        return NULL;
    }

    ccon_node* node_struct = malloc(sizeof(ccon_node));
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

ccon_node* ccon_copy_node(ccon_node* node_struct) {
    if (node_struct == NULL) {
        return NULL;
    }

    return ccon_create_node(ccon_n_copy_id(node_struct->id),
                            ccon_n_copy_role(node_struct->role),
                            ccon_n_copy_address(node_struct->address),
                            ccon_n_copy_actions(node_struct->actions),
                            ccon_n_copy_background_tasks(node_struct->background_tasks),
                            ccon_n_copy_servers(node_struct->servers),
                            ccon_n_copy_contacts(node_struct->contacts));
}

ccon_node* ccon_create_default_node() {
    ccon_n_node_id* id = ccon_n_create_id(NULL, NULL, 0, 0);
    if (id == NULL) {
        return NULL;
    }

    ccon_n_node_role* role = ccon_n_create_role(NULL, NULL, 0, 0);
    if (role == NULL) {
        return NULL;
    }

    ccon_n_node_address* address = ccon_n_create_address(NULL, NULL, 0, 0);
    if (address == NULL) {
        return NULL;
    }

    ccon_n_node_actions* actions = ccon_n_create_actions(NULL, 0);
    if (actions == NULL) {
        return NULL;
    }

    ccon_n_node_background_tasks* background_tasks = ccon_n_create_background_tasks(NULL, NULL);
    if (background_tasks == NULL) {
        return NULL;
    }

    ccon_n_node_servers* servers = ccon_n_create_servers(NULL, 0);
    if (servers == NULL) {
        return NULL;
    }

    ccon_n_node_contacts* contacts = ccon_n_create_contacts(NULL, 0);
    if (contacts == NULL) {
        return NULL;
    }

    return ccon_create_node(id, role, address, actions, background_tasks, servers, contacts);
}

int ccon_delete_node(ccon_node** node) {
    if (node == NULL || (*node) == NULL) {
        return 0;
    }

    if (ccon_n_delete_id((*node)->id) != 0) {
        return -1;
    }

    if (ccon_n_delete_role((*node)->role) != 0) {
        return -1;
    }

    if (ccon_n_delete_address(&((*node)->address)) != 0) {
        return -1;
    }

    if (ccon_n_delete_actions(&((*node)->actions)) != 0) {
        return -1;
    }

    if (ccon_n_delete_background_tasks((*node)->background_tasks) != 0) {
        return -1;
    }

    if (ccon_n_delete_servers((*node)->servers) != 0) {
        return -1;
    }

    if (ccon_n_delete_contacts((*node)->contacts) != 0) {
        return -1;
    }

    free((*node));
    *node = NULL;
    return 0;
}

int ccon_edit_node(ccon_node* node_struct,
                   ccon_n_node_id* id,
                   ccon_n_node_role* role,
                   ccon_n_node_address* address,
                   ccon_n_node_actions* actions,
                   ccon_n_node_background_tasks* background_tasks,
                   ccon_n_node_servers* servers,
                   ccon_n_node_contacts* contacts,
                   int deep_copy) {
    if (node_struct == NULL) {
        return -1;
    }

    if (id != NULL) {
        if (ccon_n_delete_id(node_struct->id) != 0) {
            return -1;
        }
        if (deep_copy == 0) {
            node_struct->id = ccon_n_copy_id(id);
        } else {
            node_struct->id = id;
        }
    }

    if (role != NULL) {
        if (ccon_n_delete_role(node_struct->role) != 0) {
            return -1;
        }
        if (deep_copy == 0) {
            node_struct->role = ccon_n_copy_role(role);
        } else {
            node_struct->role = role;
        }
    }

    if (address != NULL) {
        if (ccon_n_delete_address((&node_struct->address)) != 0) {
            return -1;
        }
        if (deep_copy == 0) {
            node_struct->address = ccon_n_copy_address(address);
        } else {
            node_struct->address = address;
        }
    }

    if (actions != NULL) {
        if (ccon_n_delete_actions(&(node_struct->actions)) != 0) {
            return -1;
        }
        if (deep_copy == 0) {
            node_struct->actions = ccon_n_copy_actions(actions);
        } else {
            node_struct->actions = actions;
        }
    }

    if (background_tasks != NULL) {
        if (ccon_n_delete_background_tasks(node_struct->background_tasks) != 0) {
            return -1;
        }
        if (deep_copy == 0) {
            node_struct->background_tasks = ccon_n_copy_background_tasks(background_tasks);
        } else {
            node_struct->background_tasks = background_tasks;
        }
    }

    if (servers != NULL) {
        if (ccon_n_delete_servers(node_struct->servers) != 0) {
            return -1;
        }
        if (deep_copy == 0) {
            node_struct->servers = ccon_n_copy_servers(servers);
        } else {
            node_struct->servers = servers;
        }
    }

    if (contacts != NULL) {
        if (ccon_n_delete_contacts(node_struct->contacts) != 0) {
            return -1;
        }
        if (deep_copy == 0) {
            node_struct->contacts = ccon_n_copy_contacts(contacts);
        } else {
            node_struct->contacts = contacts;
        }
    }

    return 0;
}
