#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "../include/node/servers.h"
}

class ServersTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

static void* TestFunctionServe(void* value) {
    return nullptr;
}

// Test background_tasks creation and deletion
TEST_F(ServersTest, ServersCreationAndDeletion) {
    // create components
    // create two servers
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

    // create address and assert successful creation
    node_address* address = create_address(char_addresses,
                                           integer_addresses,
                                           char_address_count,
                                           integer_address_count);
    ASSERT_NE(address, nullptr);


    node_single_server* single_server_one = create_single_server(address, &TestFunctionServe);
    ASSERT_NE(single_server_one, nullptr);

    // create address and assert successful creation
    node_address* address_two = create_address(char_addresses,
                                           integer_addresses,
                                           char_address_count,
                                           integer_address_count);
    ASSERT_NE(address_two, nullptr);

    node_single_server* single_server_two = create_single_server(address_two, &TestFunctionServe);
    ASSERT_NE(single_server_two, nullptr);

    node_single_server** server_array = (node_single_server**) malloc(sizeof(node_single_server*) * 2);
    server_array[0] = single_server_one;
    server_array[1] = single_server_two;

    int server_count = 2;

    node_servers* servers = create_servers(server_array, server_count);
    ASSERT_NE(servers, nullptr);

    int result = delete_servers(servers);
    ASSERT_EQ(result, 0);

    free(server_array);
    free(integer_addresses);
    free(char_addresses[0]);
    free(char_addresses[1]);
    free(char_addresses[2]);
    free(char_addresses);
}
