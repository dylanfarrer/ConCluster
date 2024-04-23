#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include "../include/cluster.h"
}

class ClusterTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

static void* TestFunctionOne(void* value) {
    return nullptr;
}

static void* TestFunctionTwo(void* value) {
    return nullptr;
}

static void* TestFunctionThree(void* value) {
    return nullptr;
}

static void* TestFunctionSchedule(void* value) {
    return nullptr;
}

static void* TestFunctionServe(void* value) {
    return nullptr;
}

static ccon_n_node_id* create_id_struct() {
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

    int char_id_count = 3;
    int integer_id_count = 3;
    ccon_n_node_id* id = ccon_n_create_id(char_ids,
                            integer_ids,
                            char_id_count,
                            integer_id_count);

    free(integer_ids);
    free(char_ids[0]);
    free(char_ids[1]);
    free(char_ids[2]);
    free(char_ids);

    return id;
}

static ccon_n_node_role* create_role_struct() {
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

    int char_role_count = 3;
    int integer_role_count = 3;
    ccon_n_node_role* role = ccon_n_create_role(char_roles,
                                  integer_roles,
                                  char_role_count,
                                  integer_role_count);

    free(integer_roles);
    free(char_roles[0]);
    free(char_roles[1]);
    free(char_roles[2]);
    free(char_roles);

    return role;
}

static ccon_n_node_address* create_address_struct() {
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
    ccon_n_node_address* address = ccon_n_create_address(char_addresses,
                                           integer_addresses,
                                           char_address_count,
                                           integer_address_count);
    
    free(integer_addresses);
    free(char_addresses[0]);
    free(char_addresses[1]);
    free(char_addresses[2]);
    free(char_addresses);

    return address;
}

static node_actions* create_actions_struct() {
    Action* actions_array = (Action*) malloc(3 * sizeof(Action));
    actions_array[0] = &TestFunctionOne;
    actions_array[1] = &TestFunctionTwo;
    actions_array[2] = &TestFunctionThree;

    int action_count = 3;

    node_actions* actions = create_actions(actions_array, action_count);

    free(actions_array);
    return actions;
}

static node_background_tasks* create_background_tasks_struct() {
    return create_background_tasks(create_actions_struct(), &TestFunctionSchedule);
}

static node_servers* create_servers_struct() {
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

    ccon_n_node_address* address = ccon_n_create_address(char_addresses,
                                           integer_addresses,
                                           char_address_count,
                                           integer_address_count);

    node_single_server* single_server_one = create_single_server(address, &TestFunctionServe);

    ccon_n_node_address* address_two = ccon_n_create_address(char_addresses,
                                           integer_addresses,
                                           char_address_count,
                                           integer_address_count);

    node_single_server* single_server_two = create_single_server(address_two, &TestFunctionServe);

    node_single_server** server_array = (node_single_server**) malloc(sizeof(node_single_server*) * 2);
    server_array[0] = single_server_one;
    server_array[1] = single_server_two;

    int server_count = 2;

    node_servers* servers = create_servers(server_array, server_count);

    free(server_array);
    free(integer_addresses);
    free(char_addresses[0]);
    free(char_addresses[1]);
    free(char_addresses[2]);
    free(char_addresses);

    return servers;
}

static node_contacts* create_contacts_struct() {
    ccon_n_node_address* address_one = create_address_struct();
    ccon_n_node_address* address_two = create_address_struct();


    ccon_n_node_address** address_array = (ccon_n_node_address**) malloc(sizeof(ccon_n_node_address*) * 2);
    address_array[0] = address_one;
    address_array[1] = address_two;

    int address_count = 2;

    node_contacts* contacts = create_contacts(address_array, address_count);

    free(address_array);

    return contacts;
}

static ccon_node* create_node_struct() {
    ccon_node* node_struct = ccon_create_node(create_id_struct(),
                                    create_role_struct(),
                                    create_address_struct(),
                                    create_actions_struct(),
                                    create_background_tasks_struct(),
                                    create_servers_struct(),
                                    create_contacts_struct());
    return node_struct;
}

// Test cluster creation and deletion
TEST_F(ClusterTest, ClusterCreationAndDeletion) {
    ccon_node** node_array = (ccon_node**) malloc(sizeof(ccon_node*) * 2);
    node_array[0] = create_node_struct();
    node_array[1] = create_node_struct();

    int node_count = 2;

    ccon_cluster* cluster_struct = ccon_create_cluster(node_array, node_count);
    ASSERT_NE(cluster_struct, nullptr);

    int result = ccon_delete_cluster(cluster_struct);
    ASSERT_EQ(result, 0);

    free(node_array);
}

TEST_F(ClusterTest, ClusterCreationFromNode) {
    ccon_node* node_struct = ccon_create_default_node();
    ccon_cluster* cluster_struct = ccon_create_cluster_from_node(node_struct, 3);
    ASSERT_NE(cluster_struct, nullptr);
    ASSERT_EQ(cluster_struct->node_count, 3);

    ccon_delete_node(node_struct);

    int result = ccon_delete_cluster(cluster_struct);
    ASSERT_EQ(result, 0);
}

TEST_F(ClusterTest, ClusterCreationFromDefaultNode) {
    ccon_cluster* cluster_struct = ccon_create_cluster_from_default_node(3);
    ASSERT_NE(cluster_struct, nullptr);
    ASSERT_EQ(cluster_struct->node_count, 3);

    int result = ccon_delete_cluster(cluster_struct);
    ASSERT_EQ(result, 0);
}

TEST_F(ClusterTest, DeleteClusterNode) {
    ccon_cluster* cluster_struct = ccon_create_cluster_from_default_node(3);
    ASSERT_NE(cluster_struct, nullptr);
    ASSERT_EQ(cluster_struct->node_count, 3);

    int delete_result = ccon_delete_cluster_node(cluster_struct, 2);
    ASSERT_EQ(delete_result, 0);
    ASSERT_EQ(cluster_struct->node_count, 2);

    int result = ccon_delete_cluster(cluster_struct);
    ASSERT_EQ(result, 0);
}

TEST_F(ClusterTest, ShallowEditClusterNode) {
    ccon_cluster* cluster_struct = ccon_create_cluster_from_default_node(3);
    ASSERT_NE(cluster_struct, nullptr);
    ASSERT_EQ(cluster_struct->node_count, 3);

    ASSERT_EQ(cluster_struct->nodes[2]->address->character_address_count, 0);

    ccon_n_node_address* address = create_address_struct();
    int edit_result = ccon_edit_cluster_node(cluster_struct,
                                        2,
                                        nullptr,
                                        nullptr,
                                        address,
                                        nullptr,
                                        nullptr,
                                        nullptr,
                                        nullptr,
                                        1);
    ASSERT_EQ(edit_result, 0);

    ASSERT_EQ(cluster_struct->nodes[2]->address->character_address_count, 3);

    int result = ccon_delete_cluster(cluster_struct);
    ASSERT_EQ(result, 0);
}

TEST_F(ClusterTest, DeepEditClusterNode) {
    ccon_cluster* cluster_struct = ccon_create_cluster_from_default_node(3);
    ASSERT_NE(cluster_struct, nullptr);
    ASSERT_EQ(cluster_struct->node_count, 3);

    ASSERT_EQ(cluster_struct->nodes[2]->id->character_id_count, 0);

    ccon_n_node_id* id = create_id_struct();
    int edit_result = ccon_edit_cluster_node(cluster_struct,
                                        2,
                                        id,
                                        nullptr,
                                        nullptr,
                                        nullptr,
                                        nullptr,
                                        nullptr,
                                        nullptr,
                                        0);
    ASSERT_EQ(edit_result, 0);
    ccon_n_delete_id(id);

    ASSERT_EQ(cluster_struct->nodes[2]->id->character_id_count, 3);

    int result = ccon_delete_cluster(cluster_struct);
    ASSERT_EQ(result, 0);
}
