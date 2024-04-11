#include "../include/node.h"

#include <stdlib.h>
#include <stdio.h>

// ----------------------- creation / deletion -----------------------

node* create_node(node_id* id,
                  node_role* role,
                  node_address* address,
                  node_actions* actions,
                  node_background_tasks* background_tasks,
                  node_servers* servers,
                  node_contacts* contacts) {

    if (id == NULL || \
        role == NULL || \
        address == NULL || \
        actions == NULL || \
        background_tasks == NULL || \
        servers == NULL || \
        contacts == NULL) {
        return NULL;
    }

    node* node = malloc(sizeof(node));
    if (node == NULL) {
        return NULL;
    }

    node->id = id;
    node->role = role;
    node->address = address;
    node->actions = actions;
    node->background_tasks = background_tasks;
    node->servers = servers;
    node->contacts = contacts;

    return node;
}

int delete_node(node* node) {
    if (node == NULL) {
        return -1;
    }

    if (delete_node_id(node->id) != 0) {
        return -1;
    }
    if (delete_node_role(node->role) != 0) {
        return -1;
    }
    if (delete_node_address(node->address) != 0) {
        return -1;
    }
    if (delete_node_actions(node->actions) != 0) {
        return -1;
    }
    if (delete_node_background_tasks(node->background_tasks) != 0) {
        return -1;
    }
    if (delete_node_servers(node->servers) != 0) {
        return -1;
    }
    if (delete_node_contacts(node->contacts) != 0) {
        return -1;
    }

    free(node);

    return 0;
}

node_id* create_node_id(char** character_ids,
                        int* integer_ids,
                        int character_id_count,
                        int integer_id_count) {
    node_id* id = malloc(sizeof(node_id));
    if (id == NULL) {
        return NULL;
    }
    id->character_ids = character_ids;
    id->integer_ids = integer_ids;
    id->character_id_count = character_id_count;
    id->integer_id_count = integer_id_count;
    return id;

}

int delete_node_id(node_id* id) {
    if (id == NULL) {
        return 0;
    }
    for (int i = 0; i < id->character_id_count; i++) {
        free(id->character_ids[i]);
    }
    free(id->character_ids);

    free(id->integer_ids);
    free(id);
    return 0;
}

node_role* create_node_role(char** character_roles,
                            int* integer_roles,
                            int character_roles_count,
                            int integer_roles_count) {
    node_role* role = malloc(sizeof(node_role));
    if (role == NULL) {
        return NULL;
    }

    role->character_roles = character_roles;
    role->integer_roles = integer_roles;
    role->character_role_count = character_roles_count;
    role->integer_role_count = integer_roles_count;

    return role;            
}

int delete_node_role(node_role* role) {
    if (role == NULL) {
        return 0;
    }
    for (int i = 0; i < role->character_role_count; i++) {
        free(role->character_roles[i]);
    }
    free(role->character_roles);

    free(role->integer_roles);
    free(role);
    return 0;
}

node_address* create_node_address(char** character_addresses,
                                  int* integer_addresses,
                                  int character_address_count,
                                  int integer_address_count) {
    node_address* address = malloc(sizeof(node_address));
    if (address == NULL) {
        return NULL;
    }

    address->character_addresses = character_addresses;
    address->integer_addresses = integer_addresses;
    address->character_address_count = character_address_count;
    address->integer_address_count = integer_address_count;

    return address;
}

int delete_node_address(node_address* address) {
    if (address == NULL) {
        return 0;
    }

    for (int i = 0; i < address->character_address_count; i++) {
        free(address->character_addresses[i]);
    }
    free(address->character_addresses);
    
    free(address->integer_addresses);
    free(address);
    return 0;
}

node_contacts* create_node_contacts(node_address** contacts, int contact_count) {
    if (contacts == NULL) {
        return NULL;
    }

    node_contacts* contacts_struct = malloc(sizeof(node_contacts));
    if (contacts_struct == NULL) {
        return NULL;
    }

    contacts_struct->contacts = contacts;
    contacts_struct->contact_count = contact_count;

    return contacts_struct;
}

int delete_node_contacts(node_contacts* contacts) {
    if (contacts == NULL) {
        return 0;
    }
    
    for (int i = 0; i < contacts->contact_count; i++) {
        if (delete_node_address(contacts->contacts[i]) != 0) {
            return -1;
        }
    }
    free(contacts->contacts);

    free(contacts);
    return 0;
}

node_actions* create_node_actions(Action* actions, int action_count) {
    node_actions* actions_struct = malloc(sizeof(node_actions));
    if (actions_struct == NULL) {
        return NULL;
    }

    actions_struct->actions = actions;
    actions_struct->action_count = action_count;

    return actions_struct;
}

int delete_node_actions(node_actions* actions) {
    if (actions == NULL) {
        return 0;
    }

    free(actions->actions);
    free(actions);
    return 0;
}

node_background_tasks* create_node_background_tasks(node_actions* actions, void* (*schedule) (void*)) {
    if (actions == NULL) {
        return NULL;
    }

    node_background_tasks* background_tasks = malloc(sizeof(node_background_tasks));
    if (background_tasks == NULL) {
        return NULL;
    }

    background_tasks->actions = actions;
    background_tasks->invocation_status = 0;
    background_tasks->schedule = schedule;

    return background_tasks;
}

int delete_node_background_tasks(node_background_tasks* background_tasks) {
    if (background_tasks == NULL) {
        return 0;
    }

    if (delete_node_actions(background_tasks->actions) != 0) {
        return -1;
    }
    free(background_tasks);
    return 0;
}

node_single_server* create_node_single_server(node_address* address, void* (*serve) (void*)) {
    if (address == NULL) {
        return NULL;
    }

    node_single_server* single_server = malloc(sizeof(node_single_server));
    if (single_server == NULL) {
        return NULL;
    }

    single_server->address = address;
    single_server->invocation_status = 0;
    single_server->serve = serve;

    return single_server;
}

int delete_node_single_server(node_single_server* single_server) {
    if (single_server == NULL) {
        return 0;
    }

    if (delete_node_address(single_server->address) != 0) {
        return -1;
    }
    free(single_server);
    return 0;
}

node_servers* create_node_servers(node_single_server** servers, int server_count) {
    if (servers == NULL) {
        return NULL;
    }

    node_servers* servers_struct = malloc(sizeof(node_servers));
    if (servers_struct == NULL) {
        return NULL;
    }

    servers_struct->servers = servers;
    servers_struct->server_count = server_count;

    return servers_struct;
}
int delete_node_servers(node_servers* servers) {
    if (servers == NULL) {
        return 0;
    }

    for (int i = 0; i < servers->server_count; i++) {
        if (delete_node_single_server(servers->servers[i]) != 0) {
            return -1;
        }
    }
    free(servers->servers);

    free(servers);
    return 0;
}

// ----------------------- function invocation -----------------------
void* invoke_server(node* node, int* server_id) {}
void* invoke_action(node* node, int* action_id) {}
void* invoke_background_scheduler(node* node) {}


// ----------------------- node member interaction -----------------------
int update_id(node* node, node_id* id) {}
int update_role(node* node, node_role* role) {}
int update_address(node* node, node_address* address) {}
int update_actions(node* node, node_actions* actions) {}
int update_background_tasks(node* node, node_background_tasks* background_tasks) {}
int update_servers(node* node, node_servers* servers) {}
int update_contacts(node* node, node_contacts* contacts) {}


// ----------------------- node_id member interaction -----------------------
int update_node_character_id(node_id* id, char* character_id, int character_id_index) {}
int update_node_integer_id(node_id* id, int integer_id, int integer_id_index) {}

int add_node_character_id(node_id* id, char* new_character_id) {}
int add_node_integer_id(node_id* id, int new_integer_id) {}

int delete_node_character_id(node_id* id, int character_id_index) {}
int delete_node_integer_id(node_id* id, int integer_id_index) {}


// ----------------------- node_role member interaction -----------------------
int update_node_character_role(node_role* role, char* character_role, int character_role_index) {}
int update_node_integer_role(node_role* role, int integer_role, int integer_role_index) {}

int add_node_character_role(node_role* role, char* new_character_role) {}
int add_node_integer_role(node_role* role, int new_integer_role) {}

int delete_node_character_role(node_role* role, int character_role_index) {}
int delete_node_integer_role(node_role* role, int integer_role_index) {}


// ----------------------- node_address member interaction -----------------------
int update_node_character_address(node_address* address, char* character_address, int character_address_index) {}
int update_node_integer_address(node_address* address, int integer_address, int integer_address_index) {}

int add_node_character_address(node_address* address, char* new_character_address) {}
int add_node_integer_address(node_address* address, int new_integer_address) {}

int delete_node_character_address(node_address* address, int character_address_index) {}
int delete_node_integer_address(node_address* address, int integer_address_index) {}


// ----------------------- node_contacts member interaction -----------------------
int update_node_contact(node_contacts* contacts, node_address* address, int contact_index) {}
int add_node_contact(node_contacts* contacts, node_address* address) {}
int delete_node_contact(node_contacts* contacts, int contact_index) {}


// ----------------------- node_actions member interaction -----------------------
int update_node_action(node_actions* actions, Action action, int action_index) {}
int add_node_action(node_actions* actions, Action action) {}
int delete_node_action(node_actions* actions, int action_index) {}


// ----------------------- node_background_tasks member interaction -----------------------
int update_node_background_tasks_scheduler(node_single_server* single_server, void* (*schedule) (void*)) {}
int update_node_background_task(node_background_tasks* background_tasks, Action background_task, int background_task_index) {}
int add_node_background_task(node_background_tasks* background_tasks, Action background_task) {}
int delete_node_background_task(node_background_tasks* background_tasks, int background_task_index) {}


// ----------------------- node_single_server member interaction -----------------------
int update_node_single_server_serve(node_single_server* single_server, void* (*serve) (void*)) {}
int update_node_single_server_address(node_single_server* single_server, node_address* address) {}


// ----------------------- node_servers member interaction -----------------------
int update_node_servers_server(node_servers* servers, node_single_server* single_server, int server_index) {}
int add_node_servers_server(node_servers* servers, node_single_server* single_server) {}
int delete_node_servers_server(node_servers* servers, int server_index) {}


// ----------------------- node_contacts member interaction -----------------------
int update_node_contacts_contact(node_contacts* contacts, node_address* address, int contact_index) {}
int add_node_contacts_contact(node_contacts* contacts, node_address* address) {}
int delete_node_contacts_contact(node_contacts* contacts, int contact_index) {}
