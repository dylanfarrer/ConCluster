#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "../include/node/single_server.h"
}

class SingleServerTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

static void* TestFunctionServe(void* value) {
    return nullptr;
}

// Test background_tasks creation and deletion
TEST_F(SingleServerTest, SingleServerCreationAndDeletion) {
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

    // create address and assert successful creation
    node_address* address = create_address(char_addresses,
                                           integer_addresses,
                                           char_address_count,
                                           integer_address_count);
    ASSERT_NE(address, nullptr);


    node_single_server* single_server = create_single_server(address, &TestFunctionServe);
    ASSERT_NE(single_server, nullptr);

    int result = delete_single_server(single_server);
    ASSERT_EQ(result, 0);

    free(integer_addresses);
    free(char_addresses[0]);
    free(char_addresses[1]);
    free(char_addresses[2]);
    free(char_addresses);
}
