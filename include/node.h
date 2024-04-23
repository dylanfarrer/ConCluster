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
    ccon_n_node_id* id;
    ccon_n_node_role* role;
    ccon_n_node_address* address;
    ccon_n_node_actions* actions;
    ccon_n_node_background_tasks* background_tasks;
    ccon_n_node_servers* servers;
    ccon_n_node_contacts* contacts;
} ccon_node;

/**
 * @brief Create a ccon_node struct.
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
 * @return ccon_node* struct or NULL
 */
ccon_node* ccon_create_node(ccon_n_node_id* id,
                            ccon_n_node_role* role,
                            ccon_n_node_address* address,
                            ccon_n_node_actions* actions,
                            ccon_n_node_background_tasks* background_tasks,
                            ccon_n_node_servers* servers,
                            ccon_n_node_contacts* contacts);

/**
 * @brief Create a ccon_node from node_struct struct.
 * Performs deep copy on node_struct struct.
 * if malloc fails or node_struct struct is NULL, return NUL.
 * 
 * @param node_struct node to deep copy
 * @return ccon_node* node struct or NULL
 */
ccon_node* ccon_copy_node(ccon_node* node_struct);

/**
 * @brief Create a ccon_node struct and populates members with default (nullified) structs.
 * Note: members are not null, but will contain null members themselves.
 * if malloc fails, returns NULL.
 * 
 * @return ccon_node* struct or NULL
 */
ccon_node* ccon_create_default_node();

/**
 * @brief deletes a ccon_node struct;
 * Calls underlying delete functions for each member, if any fail, delete operation is cancelled
 * - but not recovered from.
 * 
 * @param node struct to free
 * @return int 0 on success, -1 on failure.
 */
int ccon_delete_node(ccon_node* node);


/**
 * @brief Edits a ccon_node struct in place.
 * If deep_copy is 0, a deep copy is performed, else the struct members are 
 * shallow copied.
 * Any member argument that is not required to change should be NULL.
 * If edit fails, -1 is returned.
 * 
 * @param node struct to edit
 * @param id 
 * @param role 
 * @param address 
 * @param actions 
 * @param background_tasks 
 * @param servers 
 * @param contacts 
 * @param deep_copy 
 * @return int 0 on success, -1 on failure.
 */
int ccon_edit_node(ccon_node* node_struct,
                    ccon_n_node_id* id,
                    ccon_n_node_role* role,
                    ccon_n_node_address* address,
                    ccon_n_node_actions* actions,
                    ccon_n_node_background_tasks* background_tasks,
                    ccon_n_node_servers* servers,
                    ccon_n_node_contacts* contacts,
                    int deep_copy);

#endif
