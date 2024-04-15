#ifndef CLUSTER_H
#define CLUSTER_H

#include "node.h"

/**
 * @brief struct to represent a cluster - a group of nodes.
 * This struct is minimal in order to not impose on any cluster design.
 * Additional cluster-level logic should be implemented in a wrapper.
 * For creation/deletion information on for the node array, see node.h
 */
typedef struct {
    node** nodes;
    int node_count;
} cluster;

/**
 * @brief Create a cluster struct.
 * Creates new node* array, but performs a shallow copy on each item.
 * if malloc fails, nodes is null or node_count is negative, returns NULL.
 * 
 * @param nodes 
 * @param node_count 
 * @return cluster* struct or NULL.
 */
cluster* create_cluster(node** nodes, int node_count);

/**
 * @brief Create a cluster struct, cloning a copy_node struct node_count times.
 * Deep copies each struct and original copy_node is not included in cluster.
 * if malloc fails, copy_node is null or node_count is negative, returns NULL.
 * 
 * @param copy_node node struct to clone, cannot be NULL
 * @param node_count number of nodes to create.
 * @return cluster* cluster struct or NULL.
 */
cluster* create_cluster_from_node(node* copy_node, int node_count);

/**
 * @brief Create a cluster of population node_count from default node struct.
 * if malloc fails or node_count is negative, returns NULL.
 * 
 * @param node_count number of nodes to have in struct.
 * @return cluster* cluster struct or NULL.
 */
cluster* create_cluster_from_default_node(int node_count);

/**
 * @brief deletes a cluster struct.
 * Calls underlying delete function for node, if any fail, delete operation is cancelled.
 * 
 * 
 * @param cluster struct to free.
 * @return int 0 on success, -1 on failure.
 */
int delete_cluster(cluster* cluster);

#endif
