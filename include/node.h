#ifndef NODE_H
#define NODE_H

#include "node/id.h"
#include "node/role.h"
#include "node/address.h"
#include "node/actions.h"
#include "node/background_tasks.h"
#include "node/servers.h"
#include "node/single_server.h"
#include "node/contacts.h"

/**
 * @brief struct to represent a single node, designed to hold all the traits
 * to act/exist within a multi-agent/distributed/p2p system.
 * For creation/deletion information on each individual member, see
 * corresponding headers. (id.h, role.h, address.h ...)
 */
typedef struct {
    node_id* id;
    node_role* role;
    node_address* address;
    node_actions* actions;
    node_background_tasks* background_tasks;
    node_servers* servers;
    node_contacts* contacts;
} node;

/**
 * @brief Create a node struct.
 * Performs a shallow copy on each member.
 * if malloc fails or any struct is NULL, returns NULL.
 * 
 * @param id
 * @param role 
 * @param address 
 * @param actions 
 * @param background_tasks 
 * @param servers 
 * @param contacts 
 * @return node* struct or NULL
 */
node* create_node(node_id* id,
                  node_role* role,
                  node_address* address,
                  node_actions* actions,
                  node_background_tasks* background_tasks,
                  node_servers* servers,
                  node_contacts* contacts);

/**
 * @brief Create a node from copy_node struct.
 * Performs deep copy on copy_node struct.
 * if malloc fails or copy_node struct is NULL, return NUL.
 * 
 * @param copy_node node to deep copy
 * @return node* node struct or NULL
 */
node* create_node_from_node(node* copy_node);

/**
 * @brief Create a node struct and populates members with default (nullified) structs.
 * Note: members are not null, but will contain null members themselves.
 * if malloc fails, returns NULL.
 * Utilises create_node_from_node.
 * 
 * @return node* struct or NULL
 */
node* create_default_node();

/**
 * @brief deletes a node struct;
 * Calls underlying delete functions for each member, if any fail, delete operation is cancelled
 * - but not recovered from.
 * 
 * @param node struct to free
 * @return int 0 on success, -1 on failure.
 */
int delete_node(node* node);

#endif
