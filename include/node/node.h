#ifndef NODE_H
#define NODE_H

#include "id.h"
#include "role.h"
#include "address.h"
#include "actions.h"
#include "background_tasks.h"
#include "servers.h"
#include "single_server.h"
#include "contacts.h"

typedef struct {
    node_id* id;
    node_role* role;
    node_address* address;
    node_actions* actions;
    node_background_tasks* background_tasks;
    node_servers* servers;
    node_contacts* contacts;
} node;

node* create_node(node_id* id,
                  node_role* role,
                  node_address* address,
                  node_actions* actions,
                  node_background_tasks* background_tasks,
                  node_servers* servers,
                  node_contacts* contacts);

int delete_node(node* node);


#endif