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
