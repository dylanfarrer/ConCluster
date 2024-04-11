#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include "../include/node.h"
}

class NodeTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

void* testNodeFunction(void* args) {
    return nullptr;
}

// Test node creation and deletion
TEST_F(NodeTest, NodeCreationAndDeletion) {
    // create components
    char** char_ids = (char**) malloc(3 * sizeof(char*));
    char_ids[0] = (char*) malloc(12 * sizeof(char));
    char_ids[1] = (char*) malloc(12 * sizeof(char));
    char_ids[2] = (char*) malloc(12 * sizeof(char));
    strcpy(char_ids[0], "hello world");
    strcpy(char_ids[1], "hello world");
    strcpy(char_ids[2], "hello world");

    int* integer_ids = (int*) malloc(3 * sizeof(int));
    integer_ids[0] = 1;
    integer_ids[1] = 2;
    integer_ids[2] = 3;

    int char_ids_count = 3;
    int integer_ids_count = 3;

    node_id* id = create_node_id(char_ids, integer_ids, char_ids_count, integer_ids_count);
    ASSERT_NE(id, nullptr);


    // create components
    char** char_roles = (char**) malloc(3 * sizeof(char*));
    char_roles[0] = (char*) malloc(12 * sizeof(char));
    char_roles[1] = (char*) malloc(12 * sizeof(char));
    char_roles[2] = (char*) malloc(12 * sizeof(char));
    strcpy(char_roles[0], "hello world");
    strcpy(char_roles[1], "hello world");
    strcpy(char_roles[2], "hello world");

    int* integer_roles = (int*) malloc(3 * sizeof(int));
    integer_roles[0] = 1;
    integer_roles[1] = 2;
    integer_roles[2] = 3;

    int char_roles_count = 3;
    int integer_roles_count = 3;
    node_role* role = create_node_role(char_roles, integer_roles, char_roles_count, integer_roles_count);
    ASSERT_NE(role, nullptr);

    
    // create components
    char** char_addresses = (char**) malloc(3 * sizeof(char*));
    char_addresses[0] = (char*) malloc(12 * sizeof(char));
    char_addresses[1] = (char*) malloc(12 * sizeof(char));
    char_addresses[2] = (char*) malloc(12 * sizeof(char));
    strcpy(char_addresses[0], "hello world");
    strcpy(char_addresses[1], "hello world");
    strcpy(char_addresses[2], "hello world");

    int* integer_addresses = (int*) malloc(3 * sizeof(int));
    integer_addresses[0] = 1;
    integer_addresses[1] = 2;
    integer_addresses[2] = 3;

    int char_address_count = 3;
    int integer_address_count = 3;
    node_address* address = create_node_address(char_addresses, integer_addresses, char_address_count, integer_address_count);
    ASSERT_NE(address, nullptr);


    // create components
    Action* actions_array = (Action*) malloc(sizeof(Action));
    actions_array[0] = &testNodeFunction;
    
    int action_count = 1;
    node_actions* actions = create_node_actions(actions_array, action_count);
    ASSERT_NE(actions, nullptr);

    // create components
    // create new node_action struct
    Action* actions_array_two = (Action*) malloc(sizeof(Action));
    actions_array_two[0] = &testNodeFunction;
    
    int action_count_two = 1;
    node_actions* inner_actions = create_node_actions(actions_array_two, action_count_two);
    Action schedule = &testNodeFunction;

    node_background_tasks* background_tasks = create_node_background_tasks(inner_actions, schedule);
    ASSERT_NE(background_tasks, nullptr);


    //create components
    node_single_server** server_array = (node_single_server**) malloc(sizeof(node_single_server*));

    // create another address struct
    char** inner_char_addresses = (char**) malloc(3 * sizeof(char*));
    inner_char_addresses[0] = (char*) malloc(12 * sizeof(char));
    inner_char_addresses[1] = (char*) malloc(12 * sizeof(char));
    inner_char_addresses[2] = (char*) malloc(12 * sizeof(char));
    strcpy(inner_char_addresses[0], "hello world");
    strcpy(inner_char_addresses[1], "hello world");
    strcpy(inner_char_addresses[2], "hello world");

    int* inner_integer_addresses = (int*) malloc(3 * sizeof(int));
    inner_integer_addresses[0] = 1;
    inner_integer_addresses[1] = 2;
    inner_integer_addresses[2] = 3;

    int inner_char_address_count = 3;
    int inner_integer_address_count = 3;
    node_address* inner_address = create_node_address(inner_char_addresses,
                                                      inner_integer_addresses,
                                                      inner_char_address_count,
                                                      inner_integer_address_count);
    
    server_array[0] = create_node_single_server(inner_address, &testNodeFunction);
    ASSERT_NE(server_array[0], nullptr);

    int server_count = 1;
    node_servers* servers = create_node_servers(server_array, server_count);
    ASSERT_NE(servers, nullptr);


    // create components
    node_address** contact_array = (node_address**) malloc(sizeof(node_address*));
    // create inner address
    char** inner_contacts_char_addresses = (char**) malloc(3 * sizeof(char*));
    inner_contacts_char_addresses[0] = (char*) malloc(12 * sizeof(char));
    inner_contacts_char_addresses[1] = (char*) malloc(12 * sizeof(char));
    inner_contacts_char_addresses[2] = (char*) malloc(12 * sizeof(char));
    strcpy(inner_contacts_char_addresses[0], "hello world");
    strcpy(inner_contacts_char_addresses[1], "hello world");
    strcpy(inner_contacts_char_addresses[2], "hello world");

    int* inner_contacts_integer_addresses = (int*) malloc(3 * sizeof(int));
    inner_contacts_integer_addresses[0] = 1;
    inner_contacts_integer_addresses[1] = 2;
    inner_contacts_integer_addresses[2] = 3;

    int inner_contacts_char_address_count = 3;
    int inner_contacts_integer_address_count = 3;
    contact_array[0] = create_node_address(inner_contacts_char_addresses,
                                           inner_contacts_integer_addresses,
                                           inner_contacts_char_address_count,
                                           inner_contacts_integer_address_count);
    int contact_count = 1;
    node_contacts* contacts = create_node_contacts(contact_array, contact_count);
    ASSERT_NE(contacts, nullptr);

    // Create node
    node* node = create_node(id, role, address, actions, background_tasks, servers, contacts);
    ASSERT_NE(node, nullptr); // Check if node creation was successful

    // Delete node
    int result = delete_node(node);
    EXPECT_EQ(result, 0); // Check if node deletion was successful (calls all other deletes internally)
}
