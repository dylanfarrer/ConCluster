#include "include/cluster.h"

#include <stdlib.h>
#include <memory.h>

ccon_cluster* ccon_create_cluster(ccon_node** nodes, int node_count) {
    if (nodes == NULL || node_count < 1) {
        return NULL;
    }

    for(int i = 0; i < node_count; i++) {
        if (nodes[i] == NULL) {
            return NULL;
        }
    }

    ccon_cluster* cluster_struct = malloc(sizeof(ccon_cluster));
    if (cluster_struct == NULL) {
        return NULL;
    }

    cluster_struct->nodes = malloc(sizeof(ccon_node*) * node_count);
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

ccon_cluster* ccon_create_cluster_from_node(ccon_node* node_struct,
                                            int node_count,
                                            int include_node) {
    if (node_count < 1 || node_struct == NULL) {
        return NULL;
    }

    ccon_node** node_array = malloc(sizeof(ccon_node*) * node_count);
    if (node_array == NULL) {
        return NULL;
    }

    if (include_node == 0) {
        node_array[0] = node_struct;
    } else {
        node_array[0] = ccon_copy_node(node_struct);
        if (node_array[0] == NULL) {
            free(node_array);
            return NULL;
        }
    }
    
    for (int i = 1; i < node_count; i++) {
        node_array[i] = ccon_copy_node(node_struct);
        if (node_array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(node_array[j]);
            }
            free(node_array);
            return NULL;
        }
    }

    ccon_cluster* cluster_struct = ccon_create_cluster(node_array, node_count);
    if (cluster_struct == NULL) {
        free(node_array);
        return NULL;
    }

    free(node_array);
    return cluster_struct;
}

ccon_cluster* ccon_create_cluster_from_default_node(int node_count) {
    if (node_count < 1) {
        return NULL;
    }

    ccon_node* default_node = ccon_create_default_node();

    ccon_cluster* cluster_struct = ccon_create_cluster_from_node(default_node, node_count, 0);
    if (cluster_struct == NULL) {
        return NULL;
    } else {
        return cluster_struct;
    }
}

int ccon_delete_cluster(ccon_cluster** cluster) {
    if (cluster == NULL || (*cluster) == NULL) {
        return 0;
    }

    if ((*cluster)->node_count < 0) {
        return -1;
    }

    if ((*cluster)->nodes != NULL) {
        for (int i = 0; i < (*cluster)->node_count; i++) {
            ccon_delete_node(&(*cluster)->nodes[i]);
        }
        free((*cluster)->nodes);
    }
    free((*cluster));
    *cluster = NULL;
    return 0;
}

int ccon_delete_cluster_node(ccon_cluster* cluster_struct, int node_index) {
    if (cluster_struct == NULL || cluster_struct->nodes == NULL || \
        cluster_struct->node_count <= node_index || node_index < 0) {
        return 0;
    }

    // create temp array
    ccon_node** cluster_array = malloc(sizeof(ccon_node*) * (cluster_struct->node_count - 1));
    if (cluster_array == NULL) {
        return -1;
    }

    // populate array (minus the element to delete)
    for (int i = 0; i < node_index; i++) {
        cluster_array[i] = cluster_struct->nodes[i];
    }
    for (int i = node_index + 1; i < cluster_struct->node_count; i++) {
        cluster_array[i - 1] = cluster_struct->nodes[i];
    }

    // free elemnt to delete and old array
    ccon_delete_node(&cluster_struct->nodes[node_index]);
    free(cluster_struct->nodes);

    // re allocate nodes
    cluster_struct->nodes = malloc(sizeof(ccon_node*) * (cluster_struct->node_count - 1));
    if (cluster_struct->nodes == NULL) {
        for (int i = 0; i < cluster_struct->node_count - 1; i++) {
            free(cluster_array[i]);
        }
        free(cluster_array);
        return -1;
    }

    // populate cluster_struct nodes
    for (int i = 0; i < cluster_struct->node_count - 1; i++ ) {
        cluster_struct->nodes[i] = cluster_array[i];
    }
    
    cluster_struct->node_count = cluster_struct->node_count - 1;

    // free temp array
    free(cluster_array);

    return 0;
}

int ccon_edit_cluster_node(ccon_cluster* cluster,
                           int node_index,
                           ccon_n_node_id* id,
                           ccon_n_node_role* role,
                           ccon_n_node_address* address,
                           ccon_n_node_actions* actions,
                           ccon_n_node_background_tasks* background_tasks,
                           ccon_n_node_servers* servers,
                           ccon_n_node_contacts* contacts,
                           int deep_copy) {
    if (cluster == NULL || \
        node_index < 0 || \
        node_index >= cluster->node_count || \
        cluster->nodes[node_index] == NULL) {
        return -1;
    }

    return ccon_edit_node(cluster->nodes[node_index],
                          id,
                          role,
                          address,
                          actions,
                          background_tasks,
                          servers,
                          contacts,
                          deep_copy);
}

int ccon_insert_cluster_node(ccon_cluster* cluster, ccon_node* node, int node_index) {
    if (cluster == NULL || \
        node_index < 0 || \
        node_index > cluster->node_count || \
        node == NULL) {
        return -1;
    }

    ccon_node** temp_nodes = cluster->nodes;

    cluster->nodes = realloc(cluster->nodes, sizeof(ccon_node*) * (cluster->node_count + 1));
    if (cluster->nodes == NULL) {
        cluster->nodes = temp_nodes;
        return -1;
    }

    for (int i = cluster->node_count; i > node_index; i--) {
        cluster->nodes[i] = cluster->nodes[i - 1];
    }

    cluster->nodes[node_index] = node;

    cluster->node_count = cluster->node_count + 1;
    return 0;
}
