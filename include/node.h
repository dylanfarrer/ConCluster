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
    node_address* contacts;
    int contact_count;
} node_contacts;

typedef struct {
    Action* actions;
    int action_count;
} node_actions;

typedef struct {
    node_actions actions;
    int invocation_status;
    void* (*schedule) (void*);
} node_background_tasks;

typedef struct {
    node_address address;
    int invocation_status;
    void* (*serve) (void*);
} node_single_server;

typedef struct {
    node_single_server* servers;
    int server_count;
} node_servers;

typedef struct {
    node_id* id;
    node_role* role;
    node_address* address;
    node_actions* actions;
    node_background_tasks* background_tasks;
    node_servers* servers;
    node_contacts* contacts;
} node;


// ----------------------- creation / deletion -----------------------

node* create_node(node_id* id,
                  node_role* role,
                  node_address* address,
                  node_actions* actions,
                  node_background_tasks* background_tasks,
                  node_servers* servers,
                  node_contacts* contacts);

int delete_node(node* node);

node_id* creat_node_id(const char** character_ids, int* integer_ids);
int delete_node_id(node_id* id);

node_role* create_node_role(const char* const* character_roles, const int* integer_roles);
int delete_node_role(node_role* role);

node_address* create_node_address(const char* const* character_addresses, const int* integer_addresses);
int delete_node_role(node_address* role);

node_contacts* create_node_contacts(const node_address* contacts);
int delete_node_contacts(node_contacts* contacts);

node_actions* create_node_actions(const Action* actions);
int delete_node_actions(node_actions* actions);

node_background_tasks* create_node_background_tasks(const node_actions* actions, void* (*schedule) (void*));
int delete_node_background_tasks(node_background_tasks* background_tasks);

node_single_server* create_node_single_server(const node_address* address, void* (*serve) (void*));
int delete_node_single_server(node_single_server* single_server);

node_servers* create_node_servers(const node_single_server* servers);
int delete_node_servers(node_servers* servers);

node_contacts* create_node_contacts(const node_address* contacts);
int delete_node_contacts(node_contacts* contacts);

// ----------------------- function invocation -----------------------
void* invoke_server(node* node, int* server_id);
void* invoke_action(node* node, int* action_id);
void* invoke_background_scheduler(node* node);


// ----------------------- node member interaction -----------------------
int update_node_id(node* node, node_id* id);
int update_node_role(node* node, node_role* role);
int update_node_address(node* node, node_address* address);
int update_node_actions(node* node, node_actions* actions);
int update_node_background_tasks(node* node, node_background_tasks* background_tasks);
int update_node_servers(node* node, node_servers* servers);
int update_node_contacts(node* node, node_contacts* contacts);


// ----------------------- node_id member interaction -----------------------
int update_node_character_id(node_id* id, const char* character_id, int character_id_index);
int update_node_integer_id(node_id* id, int integer_id, int integer_id_index);

int add_node_character_id(node_id* id, const char* new_character_id);
int add_node_integer_id(node_id* id, int new_integer_id);

int delete_node_character_id(node_id* id, int character_id_index);
int delete_node_integer_id(node_id* id, int integer_id_index);


// ----------------------- node_role member interaction -----------------------
int update_node_character_role(node_role* role, const char* character_role, int character_role_index);
int update_node_integer_role(node_role* role, int integer_role, int integer_role_index);

int add_node_character_role(node_role* role, const char* new_character_role);
int add_node_integer_role(node_role* role, int new_integer_role);

int delete_node_character_role(node_role* role, int character_role_index);
int delete_node_integer_role(node_role* role, int integer_role_index);


// ----------------------- node_address member interaction -----------------------
int update_node_character_address(node_address* address, const char* character_address, int character_address_index);
int update_node_integer_address(node_address* address, int integer_address, int integer_address_index);

int add_node_character_address(node_address* address, const char* new_character_address);
int add_node_integer_address(node_address* address, int new_integer_address);

int delete_node_character_address(node_address* address, int character_address_index);
int delete_node_integer_address(node_address* address, int integer_address_index);


// ----------------------- node_contacts member interaction -----------------------
int update_node_contact(node_contacts* contacts, node_address* address, int contact_index);
int add_node_contact(node_contacts* contacts, node_address* address);
int delete_node_contact(node_contacts* contacts, int contact_index);


// ----------------------- node_actions member interaction -----------------------
int update_node_action(node_actions* actions, Action action, int action_index);
int add_node_action(node_actions* actions, Action action);
int delete_node_action(node_actions* actions, int action_index);


// ----------------------- node_background_tasks member interaction -----------------------
int update_node_background_tasks_scheduler(node_single_server* single_server, void* (*schedule) (void*));
int update_node_background_tasks(node_background_tasks* background_tasks, Action background_task, int background_task_index);
int add_node_background_tasks(node_background_tasks* background_tasks, Action background_task);
int delete_node_background_tasks(node_background_tasks* background_tasks, int background_task_index);


// ----------------------- node_single_server member interaction -----------------------
int update_node_single_server_serve(node_single_server* single_server, void* (*serve) (void*));
int update_node_single_server_address(node_single_server* single_server, node_address* address);


// ----------------------- node_servers member interaction -----------------------
int update_node_servers_server(node_servers* servers, node_single_server* single_server, int server_index);
int add_node_servers_server(node_servers* servers, node_single_server* single_server);
int delete_node_servers_server(node_servers* servers, int server_index);


// ----------------------- node_contacts member interaction -----------------------
int update_node_contacts_contact(node_contacts* contacts, node_address* address, int contact_index);
int add_node_contacts_contact(node_contacts* contacts, node_address* address);
int delete_node_contacts_contact(node_contacts* contacts, int contact_index);

#endif
