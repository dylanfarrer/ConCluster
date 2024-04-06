#ifndef NODE_H
#define NODE_H

/*
 * node.h
 *
 * This header defines the node struct, which acts as a template for an actor in a distributed system.
 * The node struct attempts to provide an unbiased platform to build an actor, without making
 * assumptions about IDs, Roles, Actions, Background Tasks (and scheduler) and Servers.
 * 
 */

typedef void* (*Action) (void*);

typedef struct {
    char** character_ids;
    int* integer_ids;
    int character_id_count;
    int integer_id_count;
} node_id;

typedef struct {
    char** character_roles;
    int* integer_roles;
    int character_role_count;
    int integer_role_count;
} node_role;

typedef struct {
    char** character_addresses;
    int* integer_addresses;
    int character_address_count;
    int integer_address_count;
} node_address;

typedef struct {
    Action* actions;
    int action_count;
} node_actions;

typedef struct {
    node_actions actions;
    void* (*schedule) (void*);
} node_background_tasks;

typedef struct {
    node_address address;
    void (*serve) (void*);
} node_server;

typedef struct {
    node_id* id;
    node_role* role;
    node_address* address;
    node_actions* actions;
    node_background_tasks* background_tasks;
    node_server** servers;
} node;

#endif
