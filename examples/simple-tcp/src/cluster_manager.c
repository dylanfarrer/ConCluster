#include "cluster_manager.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <pthread.h>

cluster* generate_cluster(int node_count);
int perform_chatter_event(cluster* cluster_to_invoke);
int delete_cluster(cluster** cluster_to_delete);
ccon_node* create_node(void);
int delete_node(ccon_node** node);
void* node_background_action(void* args);
void* node_serve(void* args);
void* invoke_server(void* args);
void* invoke_action(void* args);

typedef struct {
    int target_port;
    const char* target_ip;
    const char* message;
    cluster* cluster_to_invoke;
} action_args;

typedef struct {
    int port;
    cluster* cluster_to_invoke;
    _Atomic int* message_counter;
} server_args;

int servers_index = 0;
int actions_index = 0;

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

int perform_chatter_event(cluster* cluster_to_invoke) {
    servers_index = 0;
    actions_index = 0;

    // perform check to ensure servers and chatter event is not already occuring

    pthread_t* server_threads[cluster_to_invoke->cluster->node_count];
    pthread_t* action_threads[cluster_to_invoke->cluster->node_count];

    server_args server_args_struct;
    server_args_struct.port = 6000;
    server_args_struct.cluster_to_invoke = cluster_to_invoke;
    server_args_struct.message_counter = &(cluster_to_invoke->message_count);
    for (int i = 0; i < cluster_to_invoke->cluster->node_count; i++) {
        server_threads[i] = run_thread(NULL, invoke_server, (void*)&server_args_struct);
        ++server_args_struct.port;
    }

    action_args action_args_struct;
    action_args_struct.target_port = 6000;
    action_args_struct.target_ip = "127.0.0.1";
    action_args_struct.message = "Hello, World!";
    action_args_struct.cluster_to_invoke = cluster_to_invoke;
    for (int i = 1; i < cluster_to_invoke->cluster->node_count; i++) {
        action_threads[i] = run_thread(NULL, invoke_action, (void*)&action_args_struct);
        ++action_args_struct.target_port;
    }
    action_threads[0] = run_thread(NULL, invoke_action, (void*)&action_args_struct);

    for (int i = 0; i < cluster_to_invoke->cluster->node_count; i++) {
        join_thread(server_threads[i], NULL);
        join_thread(action_threads[i], NULL);
    }

    // return the (hopefully) incremented message count
    return cluster_to_invoke->message_count;
}

int delete_cluster(cluster** cluster_to_delete) {
    return 0;
}

ccon_node* create_node() {
    // create custom members
    Action action_array[1] = {node_background_action};
    ccon_n_node_actions* node_actions = ccon_n_create_actions(action_array, 1);

    char* address_array[1] = {"127.0.0.1"};
    ccon_n_node_single_server* server_array[1] = { ccon_n_create_single_server(ccon_n_create_address(address_array, NULL, 1, 0), node_serve) };
    ccon_n_node_servers* node_servers = ccon_n_create_servers(server_array, 1);
    
    // return a node, filled out with default and custom members
    return ccon_create_node(ccon_n_create_id(NULL, NULL, 0, 0),
                            ccon_n_create_role(NULL, NULL, 0, 0),
                            ccon_n_create_address(NULL, NULL, 0, 0),
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

void* invoke_server(void* args) {
    int invocation_result = 0;
    server_args* parameters = args;
    ccon_n_invoke_server(parameters->cluster_to_invoke->cluster->nodes[servers_index++]->servers->servers[0],
                         &invocation_result,
                         args);
    return NULL;
}

void* invoke_action(void* args) {
    int invocation_result = 0;
    action_args* parameters = args;
    ccon_n_invoke_action(parameters->cluster_to_invoke->cluster->nodes[actions_index++]->actions,
                         0,
                         &invocation_result,
                         args);
    return NULL;
}
