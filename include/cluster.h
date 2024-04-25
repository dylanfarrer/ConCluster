#ifndef CLUSTER_H
#define CLUSTER_H

#define EXPORT __attribute__((__visibility__("default")))

#include "node.h"

/**
 * @brief struct to represent a cluster - a group of ccon_nodes.
 * This struct is minimal in order to not impose on any cluster design.
 * Additional cluster-level logic should be implemented in a wrapper.
 * For creation/deletion information on for the node array, see node.h
 */
EXPORT typedef struct {
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
EXPORT ccon_cluster* ccon_create_cluster(ccon_node** nodes, int node_count);

/**
 * @brief Create a cluster struct, cloning a node_struct struct node_count times.
 * Deep copies each struct and original copy_node is not included in cluster.
 * if malloc fails, copy_node is null or node_count is negative, returns NULL.
 * 
 * @param node_struct ccon_node struct to clone, cannot be NULL
 * @param node_count number of nodes to create.
 * @return cluster* cluster struct or NULL.
 */
EXPORT ccon_cluster* ccon_create_cluster_from_node(ccon_node* node_struct, int node_count);

/**
 * @brief Create a cluster of population node_count from default ccon_node struct.
 * if malloc fails or node_count is negative, returns NULL.
 * utilises ccon_create_cluster_from_node
 * 
 * @param node_count number of nodes to have in struct.
 * @return ccon_cluster* ccon_cluster struct or NULL.
 */
EXPORT ccon_cluster* ccon_create_cluster_from_default_node(int node_count);

/**
 * @brief deletes a ccon_cluster struct.
 * Calls underlying delete function for ccon_node, if any fail, delete operation is cancelled.
 * Sets cluster to NULL
 * 
 * @param cluster struct to free.
 * @return int 0 on success, -1 on failure.
 */
EXPORT int ccon_delete_cluster(ccon_cluster** cluster);

/**
 * @brief delete ccon_node from ccon_cluster struct.
 * Calls underlying delete function for ccon_node, if it fails, delete operation is cancelled.
 * 
 * @param cluster struct to free
 * @param node_index index of struct in ccon_cluster
 * @return int 0 on success, -1 on failure
 */
EXPORT int ccon_delete_cluster_node(ccon_cluster* cluster, int node_index);

/**
 * @brief edit a ccon_node in-place in a cluster.
 * Any ccon_node member items that are not NULL will be updated in the corresponding ccon_node.
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
EXPORT int ccon_edit_cluster_node(ccon_cluster* cluster,
                           int node_index,
                           ccon_n_node_id* id,
                           ccon_n_node_role* role,
                           ccon_n_node_address* address,
                           ccon_n_node_actions* actions,
                           ccon_n_node_background_tasks* background_tasks,
                           ccon_n_node_servers* servers,
                           ccon_n_node_contacts* contacts,
                           int deep_copy);

/**
 * @brief insert a ccon_node into the cluster.
 * ccon_node is not copied.
 * if node is null, index out of range or cluster is null, returns -1.
 * Does not accept negative node_index.
 * If node_index == cluster->node_count, node appended.
 * 
 * @param cluster pointer to cluster pointer
 * @param node 
 * @param node_index 
 * @return int 0 on success, -1 on fail.
 */
EXPORT int ccon_insert_cluster_node(ccon_cluster** cluster, ccon_node* node, int node_index);

#endif
