#include "../include/node.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    printf("deleting node\n");

    if (delete_node_id(node->id) != 0) {
        return -1;
    }
    printf("deleted node id\n");
    if (delete_node_role(node->role) != 0) {
        return -1;
    }
    printf("deleted node role\n");
    if (delete_node_address(node->address) != 0) {
        return -1;
    }
    printf("deleted node address\n");
    if (delete_node_actions(node->actions) != 0) {
        return -1;
    }
    printf("deleted node actions\n");
    if (delete_node_background_tasks(node->background_tasks) != 0) {
        return -1;
    }
    printf("deleted node background tasks\n");
    if (delete_node_servers(node->servers) != 0) {
        return -1;
    }
    printf("deleted node servers\n");
    if (delete_node_contacts(node->contacts) != 0) {
        return -1;
    }
    printf("deleted node contacts\n");

    free(node);
    printf("deleted node\n");

    return 0;
}

node_id* create_node_id(char** character_ids,
                        int* integer_ids,
                        int character_id_count,
                        int integer_id_count) {
    if (character_ids == NULL || integer_ids == NULL) {
        return NULL;
    }

    // Allocate memory for the node_id struct
    node_id* id = malloc(sizeof(node_id));
    if (id == NULL) {
        return NULL;
    }

    // Deep copy character_ids
    id->character_ids = malloc(sizeof(char*) * character_id_count);
    if (id->character_ids == NULL) {
        free(id);
        return NULL;
    }
    for (int i = 0; i < character_id_count; i++) {
        id->character_ids[i] = strdup(character_ids[i]);
        if (id->character_ids[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(id->character_ids[j]);
            }
            free(id->character_ids);
            free(id);
            return NULL;
        }
    }

    // Deep copy integer_ids
    id->integer_ids = malloc(sizeof(int) * integer_id_count);
    if (id->integer_ids == NULL) {
        for (int i = 0; i < character_id_count; i++) {
            free(id->character_ids[i]);
        }
        free(id->character_ids);
        free(id);
        return NULL;
    }
    memcpy(id->integer_ids, integer_ids, sizeof(int) * integer_id_count);

    // Set other members
    id->character_id_count = character_id_count;
    id->integer_id_count = integer_id_count;

    return id;
}

int delete_node_id(node_id* id) {
    if (id == NULL) {
        return 0;
    }

    // Free character_ids
    for (int i = 0; i < id->character_id_count; i++) {
        free(id->character_ids[i]);
    }
    free(id->character_ids);

    // Free integer_ids
    free(id->integer_ids);

    // Free node_id struct
    free(id);
    return 0;
}

node_role* create_node_role(char** character_roles, int* integer_roles, int character_role_count, int integer_role_count) {
    // Allocate memory for the node_role struct
    node_role* role = malloc(sizeof(node_role));
    if (role == NULL) {
        return NULL; // Allocation failed, return NULL
    }

    // Allocate memory for the character_roles array and copy the input strings
    role->character_roles = malloc(sizeof(char*) * character_role_count);
    if (role->character_roles == NULL) {
        free(role); // Allocation failed, free previously allocated memory
        return NULL; // Return NULL to indicate failure
    }
    for (int i = 0; i < character_role_count; i++) {
        role->character_roles[i] = strdup(character_roles[i]);
        if (role->character_roles[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(role->character_roles[j]);
            }
            free(role->character_roles);
            free(role);
            return NULL;
        }
    }

    // Allocate memory for the integer_roles array and copy the input integers
    role->integer_roles = malloc(sizeof(int) * integer_role_count);
    if (role->integer_roles == NULL) {
        for (int i = 0; i < character_role_count; i++) {
            free(role->character_roles[i]);
        }
        free(role->character_roles);
        free(role);
        return NULL;
    }
    memcpy(role->integer_roles, integer_roles, sizeof(int) * integer_role_count);

    // Set the character_role_count and integer_role_count
    role->character_role_count = character_role_count;
    role->integer_role_count = integer_role_count;

    return role; // Return the created node_role struct
}

// Function to delete a node_role struct
int delete_node_role(node_role* role) {
    if (role == NULL) {
        return 0; // Nothing to delete, return
    }

    // Free the dynamically allocated memory for character_roles
    for (int i = 0; i < role->character_role_count; i++) {
        free(role->character_roles[i]);
    }
    free(role->character_roles);

    // Free the dynamically allocated memory for integer_roles
    free(role->integer_roles);

    // Free the memory allocated for the node_role struct
    free(role);
    return 0;
}

node_address* create_node_address(char** character_addresses, int* integer_addresses, int character_address_count, int integer_address_count) {
    // Allocate memory for the node_address struct
    node_address* address = malloc(sizeof(node_address));
    if (address == NULL) {
        return NULL; // Allocation failed, return NULL
    }

    // Allocate memory for the character_addresses array and copy the input strings
    address->character_addresses = malloc(sizeof(char*) * character_address_count);
    if (address->character_addresses == NULL) {
        free(address); // Allocation failed, free previously allocated memory
        return NULL; // Return NULL to indicate failure
    }
    for (int i = 0; i < character_address_count; i++) {
        address->character_addresses[i] = strdup(character_addresses[i]);
        if (address->character_addresses[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(address->character_addresses[j]);
            }
            free(address->character_addresses);
            free(address);
            return NULL;
        }
    }

    // Allocate memory for the integer_addresses array and copy the input integers
    address->integer_addresses = malloc(sizeof(int) * integer_address_count);
    if (address->integer_addresses == NULL) {
        for (int i = 0; i < character_address_count; i++) {
            free(address->character_addresses[i]);
        }
        free(address->character_addresses);
        free(address);
        return NULL;
    }
    memcpy(address->integer_addresses, integer_addresses, sizeof(int) * integer_address_count);

    // Set the character_address_count and integer_address_count
    address->character_address_count = character_address_count;
    address->integer_address_count = integer_address_count;

    return address; // Return the created node_address struct
}

// Function to delete a node_address struct
int delete_node_address(node_address* address) {
    if (address == NULL) {
        return 0; // Nothing to delete, return
    }

    // Free the dynamically allocated memory for character_addresses
    for (int i = 0; i < address->character_address_count; i++) {
        free(address->character_addresses[i]);
    }
    free(address->character_addresses);

    // Free the dynamically allocated memory for integer_addresses
    free(address->integer_addresses);

    // Free the memory allocated for the node_address struct
    free(address);
    return 0;
}

node_contacts* create_node_contacts(node_address** contacts, int contact_count) {
    // Allocate memory for the node_contacts struct
    node_contacts* contacts_struct = malloc(sizeof(node_contacts));
    if (contacts_struct == NULL) {
        return NULL; // Allocation failed, return NULL
    }

    // Allocate memory for the contacts array and copy the input array
    contacts_struct->contacts = malloc(sizeof(node_address*) * contact_count);
    if (contacts_struct->contacts == NULL) {
        free(contacts_struct); // Allocation failed, free previously allocated memory
        return NULL; // Return NULL to indicate failure
    }
    for (int i = 0; i < contact_count; i++) {
        contacts_struct->contacts[i] = contacts[i];
    }

    // Set the contact_count
    contacts_struct->contact_count = contact_count;

    return contacts_struct; // Return the created node_contacts struct
}

// Function to delete a node_contacts struct
int delete_node_contacts(node_contacts* contacts_struct) {
    if (contacts_struct == NULL) {
        return 0; // Nothing to delete, return
    }

    // Free the dynamically allocated memory for the contacts array
    free(contacts_struct->contacts);

    // Free the memory allocated for the node_contacts struct
    free(contacts_struct);
    return 0;
}

node_actions* create_node_actions(Action* actions, int action_count) {
    // Allocate memory for the node_actions struct
    node_actions* node_actions_ptr = malloc(sizeof(node_actions));
    if (node_actions_ptr == NULL) {
        return NULL; // Allocation failed, return NULL
    }

    // Allocate memory for the actions array and copy the input array
    node_actions_ptr->actions = malloc(sizeof(Action) * action_count);
    if (node_actions_ptr->actions == NULL) {
        free(node_actions_ptr); // Allocation failed, free previously allocated memory
        return NULL; // Return NULL to indicate failure
    }
    for (int i = 0; i < action_count; i++) {
        node_actions_ptr->actions[i] = actions[i];
    }

    // Set the action_count
    node_actions_ptr->action_count = action_count;

    return node_actions_ptr; // Return the created node_actions struct
}

// Function to delete a node_actions struct
int delete_node_actions(node_actions* actions_struct) {
    if (actions_struct == NULL) {
        return 0; // Nothing to delete, return
    }

    // Free the dynamically allocated memory for the actions array
    free(actions_struct->actions);

    // Free the memory allocated for the node_actions struct
    free(actions_struct);
    return 0;
}

node_background_tasks* create_node_background_tasks(node_actions* actions, void* (*schedule)(void*)) {
    // Allocate memory for the node_background_tasks struct
    node_background_tasks* background_tasks = malloc(sizeof(node_background_tasks));
    if (background_tasks == NULL) {
        return NULL; // Allocation failed, return NULL
    }

    // Copy the input parameters to the newly created struct
    background_tasks->actions = actions;
    background_tasks->invocation_status = 0;
    background_tasks->schedule = schedule;

    return background_tasks; // Return the created node_background_tasks struct
}

// Function to delete a node_background_tasks struct
int delete_node_background_tasks(node_background_tasks* background_tasks) {
    if (background_tasks == NULL) {
        return 0; // Nothing to delete, return
    }

    // Free the memory allocated for the node_background_tasks struct
    free(background_tasks);
    return 0;
}

node_single_server* create_node_single_server(node_address* address, void* (*serve)(void*)) {
    // Allocate memory for the node_single_server struct
    node_single_server* single_server = malloc(sizeof(node_single_server));
    if (single_server == NULL) {
        return NULL; // Allocation failed, return NULL
    }

    // Set the address, invocation_status, and serve function pointer
    single_server->address = address;
    single_server->invocation_status = 0;
    single_server->serve = serve;

    return single_server; // Return the created node_single_server struct
}

// Function to delete a node_single_server struct
int delete_node_single_server(node_single_server* single_server) {
    if (single_server == NULL) {
        return 0; // Nothing to delete, return
    }

    // Free the memory allocated for the node_single_server struct
    free(single_server);
    return 0;
}

node_servers* create_node_servers(node_single_server** servers, int server_count) {
    // Allocate memory for the node_servers struct
    node_servers* servers_struct = malloc(sizeof(node_servers));
    if (servers_struct == NULL) {
        return NULL; // Allocation failed, return NULL
    }

    // Allocate memory for the servers array and copy the input array
    servers_struct->servers = malloc(sizeof(node_single_server*) * server_count);
    if (servers_struct->servers == NULL) {
        free(servers_struct); // Allocation failed, free previously allocated memory
        return NULL; // Return NULL to indicate failure
    }
    for (int i = 0; i < server_count; i++) {
        servers_struct->servers[i] = servers[i];
    }

    // Set the server_count
    servers_struct->server_count = server_count;

    return servers_struct; // Return the created node_servers struct
}

// Function to delete a node_servers struct
int delete_node_servers(node_servers* servers_struct) {
    if (servers_struct == NULL) {
        return 0; // Nothing to delete, return
    }

    // Free the dynamically allocated memory for the servers array
    free(servers_struct->servers);

    // Free the memory allocated for the node_servers struct
    free(servers_struct);
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
