#include "../include/cluster_manager.h"

#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <time.h>

cluster* generate_cluster(int node_count) {
    if (node_count > 100 || node_count < 2) {
        return NULL;
    }

    ccon_node* model_node = create_node();
    if (model_node == NULL) {
        return NULL;
    }

    ccon_cluster* cluster = ccon_create_cluster_from_node(model_node, node_count);
    if (cluster != NULL) {
        ccon_delete_node(model_node);
        return cluster;
    } else {
        ccon_delete_node(model_node);
        return NULL;
    }
}

int perform_chatter_event(cluster* cluster_to_invoke, int ms_time) {
    if (ms_time < 1000 || ms_time > 60000) {
        return -1;
    }
    
    // perform check to ensure servers and chatter event is not already occuring

    // start the servers
    int server_invocation_result = 0;
    void* premade_server_arguments;
    for (int i = 0; i < cluster_to_invoke->cluster->node_count; i++) {
        ccon_n_invoke_server(cluster_to_invoke->cluster->nodes[i]->servers->servers[0],
                             &server_invocation_result,
                             premade_server_arguments);
        if (server_invocation_result == 0) {
            // handle error
            ;
        }
        server_invocation_result = 0;
    }


    // start the actions
    // this should be threaded
    int action_invocation_result = 0;
    void* premade_action_arguments;
    for (int i = 0; i < cluster_to_invoke->cluster->node_count; i++) {
        ccon_n_invoke_action(cluster_to_invoke->cluster->nodes[i]->actions,
                             0,
                             &action_invocation_result,
                             premade_action_arguments);
        if (action_invocation_result == 0) {
            // handle error
            ;
        }
        action_invocation_result = 0;
    }

    // wait for the alloated ms_time, then join the threads

    /*
    struct timespec ts;
    ts.tv_sec = ms_time / 1000;
    ts.tv_nsec = (ms_time % 1000) * 1000000;
    nanosleep(&ts, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining thread %d\n", i);
            return EXIT_FAILURE;
        }
    }
    */

    // return the (hopefully) incremented message count
    return cluster_to_invoke->message_count;
}

int delete_cluster(cluster** cluster_to_delete) {
    return 0;
}

ccon_node* create_node() {
    return NULL;
}

int delete_node(ccon_node** node) {
    return ccon_delete_node(node);
}
