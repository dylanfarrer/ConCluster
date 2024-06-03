#include "cluster_manager.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <pthread.h>
#include <time.h>

cluster* generate_cluster(int node_count);
int perform_chatter_event(cluster* cluster_to_invoke, int ms_time);
int delete_cluster(cluster** cluster_to_delete);
ccon_node* create_node(void);
int delete_node(ccon_node** node);
void* node_background_action(void* args);
void* node_serve(void* args);

typedef struct {
    int target_port;
    const char* target_ip;
    const char* message;
} action_args;

typedef struct {
    int port;
    _Atomic int* message_counter;
} server_args;


cluster* generate_cluster(int node_count) {
    if (node_count > 100 || node_count < 2) {
        return NULL;
    }

    ccon_node* model_node = create_node();
    if (model_node == NULL) {
        return NULL;
    }

    ccon_cluster* inner_cluster = ccon_create_cluster_from_node(model_node, node_count);
    if (inner_cluster != NULL) {
        ccon_delete_node(&model_node);
        
        cluster* generate_cluster = malloc(sizeof(cluster));
        if (generate_cluster == NULL) {
            return NULL;
        }
        generate_cluster->cluster = inner_cluster;
        generate_cluster->message_count = 0;
        return generate_cluster;
    } else {
        ccon_delete_node(&model_node);
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
    // create custom members
    char* address_array[1] = {"127.0.0.1"};
    ccon_n_node_address* node_address = ccon_n_create_address(address_array, NULL, 1, 0);

    Action action_array[1] = {node_background_action};
    ccon_n_node_actions* node_actions = ccon_n_create_actions(action_array, 1);

    ccon_n_node_single_server* server_array[1] = { ccon_n_create_single_server(node_address, node_serve) };
    ccon_n_node_servers* node_servers = ccon_n_create_servers(server_array, 1);
    
    // return a node, filled out with default and custom members
    return ccon_create_node(ccon_n_create_id(NULL, NULL, 0, 0),
                            ccon_n_create_role(NULL, NULL, 0, 0),
                            node_address,
                            node_actions,
                            ccon_n_create_background_tasks(NULL, NULL),
                            node_servers,
                            ccon_n_create_contacts(NULL, 0));
}

int delete_node(ccon_node** node) {
    return ccon_delete_node(node);
}

void* node_background_action(void* args) {
    action_args* parameters = args;

    const char* ip = parameters->target_ip;
    int port = parameters->target_port;
    const char* message = parameters->message;

    char* response = send_and_recieve_on_socket(ip, port, message);

    if (response != NULL) {
        printf("Response from server: %s\n", response);
        free(response);
    } else {
        printf("Failed to receive a response from the server.\n");
    }
    return NULL;
}

void* node_serve(void* args) {
    server_args* parameters = args;
    int port = parameters->port;
    _Atomic int* message_counter = parameters->message_counter;

    char* endpoints[] = { "/" };
    FunctionPtr functions[] = {};

    int result = listen_on_socket(port, endpoints, functions, 1, 1);

    if (result == 0) {
        printf("Server successfully killed.\n");
    } else {
        printf("Error starting server.\n");
    }

    return NULL;
}
