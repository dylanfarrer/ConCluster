#include "../include/cluster.h"

#include <stdlib.h>

cluster* create_cluster(node** nodes, int node_count) {
    if (nodes == NULL || node_count < 1) {
        return NULL;
    }

    for(int i = 0; i < node_count; i++) {
        if (nodes[i] == NULL) {
            return NULL;
        }
    }

    cluster* cluster_struct = malloc(sizeof(cluster));
    if (cluster_struct == NULL) {
        return NULL;
    }

    // plus one for null terminator
    cluster_struct->nodes = malloc(sizeof(node*) * node_count);
    if (cluster_struct->nodes == NULL) {
        free(cluster_struct);
        return NULL;
    }

    for (int i = 0; i < node_count; i++ ) {
        cluster_struct->nodes[i] = nodes[i];
    }

    cluster_struct->node_count = node_count;
    return cluster_struct;
}

cluster* create_cluster_from_node(node* copy_node, int node_count) {
    if (node_count < 1 || copy_node == NULL) {
        return NULL;
    }

    node** node_array = malloc(sizeof(node*) * node_count);
    if (node_array == NULL) {
        return NULL;
    }

    node_array[0] = create_node_from_node(copy_node);
    if (node_array[0] == NULL) {
        free(node_array);
        return NULL;
    }
    
    for (int i = 1; i < node_count; i++) {
        node_array[i] = create_node_from_node(copy_node);
        if (node_array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(node_array[j]);
            }
            free(node_array);
            return NULL;
        }
    }

    cluster* cluster_struct = create_cluster(node_array, node_count);
    if (cluster_struct == NULL) {
        free(node_array);
        return NULL;
    }

    free(node_array);
    return cluster_struct;
}

cluster* create_cluster_from_default_node(int node_count) {
    if (node_count < 1) {
        return NULL;
    }

    cluster* cluster_struct = create_cluster_from_node(create_default_node(), node_count);
    if (cluster_struct == NULL) {
        return NULL;
    } else {
        return cluster_struct;
    }
}

int delete_cluster(cluster* cluster) {
    if (cluster == NULL) {
        return 0;
    }

    if (cluster->node_count < 0) {
        return -1;
    }

    if (cluster->nodes != NULL) {
        for (int i = 0; i < cluster->node_count; i++) {
            delete_node(cluster->nodes[i]);
        }
        free(cluster->nodes);
    }

    free(cluster);
    return 0;
}

int edit_cluster_node(cluster* cluster,
                      int node_index,
                      node_id* id,
                      node_role* role,
                      node_address* address,
                      node_actions* actions,
                      node_background_tasks* background_tasks,
                      node_servers* servers,
                      node_contacts* contacts,
                      int deep_copy) { return 0; }

// has to be deep copy
int edit_all_cluster_nodes(cluster* cluster,
                           node_id* id,
                           node_role* role,
                           node_address* address,
                           node_actions* actions,
                           node_background_tasks* background_tasks,
                           node_servers* servers,
                           node_contacts* contacts) { return 0; }
