#ifndef CLUSTER_H
#define CLUSTER_H

#include "node.h"

/**
 * @brief struct to represent a cluster - a group of ccon_nodes.
 * This struct is minimal in order to not impose on any cluster design.
 * Additional cluster-level logic should be implemented in a wrapper.
 * For creation/deletion information on for the node array, see node.h
 */
typedef struct {
    ccon_node** nodes;
    int node_count;
} ccon_cluster;

/**
 * @brief Create a cluster struct.
 * Creates new ccon_node* array, but performs a shallow copy on each item.
 * if malloc fails, nodes is null or node_count is negative, returns NULL.
 * 
 * @param nodes 
 * @param node_count 
 * @return cluster* struct or NULL.
 */
ccon_cluster* ccon_create_cluster(ccon_node** nodes, int node_count);

/**
 * @brief Create a cluster struct, cloning a node_struct struct node_count times.
 * Deep copies each struct and original copy_node is not included in cluster.
 * if malloc fails, copy_node is null or node_count is negative, returns NULL.
 * 
 * @param node_struct ccon_node struct to clone, cannot be NULL
 * @param node_count number of nodes to create.
 * @return cluster* cluster struct or NULL.
 */
ccon_cluster* ccon_create_cluster_from_node(ccon_node* node_struct, int node_count);

/**
 * @brief Create a cluster of population node_count from default ccon_node struct.
 * if malloc fails or node_count is negative, returns NULL.
 * utilises create_cluster_from_node
 * 
 * @param node_count number of nodes to have in struct.
 * @return cluster* cluster struct or NULL.
 */
ccon_cluster* ccon_create_cluster_from_default_node(int node_count);

/**
 * @brief deletes a cluster struct.
 * Calls underlying delete function for node, if any fail, delete operation is cancelled.
 * 
 * @param cluster struct to free.
 * @return int 0 on success, -1 on failure.
 */
int ccon_delete_cluster(ccon_cluster* cluster);

/**
 * @brief delete node from cluster struct.
 * Calls underlying delete function for node, if it fails, delete operation is cancelled.
 * 
 * @param cluster struct to free
 * @param node_index index of struct in cluster
 * @return int 0 on success, -1 on failure
 */
int ccon_delete_cluster_node(ccon_cluster* cluster, int node_index);

/**
 * @brief edit a node in-place in a cluster.
 * Any node member items that are not NULL will be updated in the corresponding node.
 * if deep copy is zero, the copy id deep, else shallow.
 * see ccon_edit_node for more info.
 * 
 * @param cluster 
 * @param node_index 
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
int ccon_edit_cluster_node(ccon_cluster* cluster,
                            int node_index,
                            node_id* id,
                            node_role* role,
                            node_address* address,
                            node_actions* actions,
                            node_background_tasks* background_tasks,
                            node_servers* servers,
                            node_contacts* contacts,
                            int deep_copy);

#endif
