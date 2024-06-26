#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include <concluster/cluster.h>
}

class SingleServerTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

static void* TestFunctionServe(void* value) {
    int* returnInt = (int*)malloc(sizeof(int));
    if (returnInt != NULL) {
        *returnInt = 1;
    }
    return returnInt;
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
    ccon_n_node_address* address = ccon_n_create_address(char_addresses,
                                                         integer_addresses,
                                                         char_address_count,
                                                         integer_address_count);
    ASSERT_NE(address, nullptr);


    ccon_n_node_single_server* single_server = ccon_n_create_single_server(address, &TestFunctionServe);
    ASSERT_NE(single_server, nullptr);

    int result = ccon_n_delete_single_server(&single_server);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(single_server, nullptr);

    free(integer_addresses);
    free(char_addresses[0]);
    free(char_addresses[1]);
    free(char_addresses[2]);
    free(char_addresses);
}

TEST_F(SingleServerTest, SingleServerCopy) {
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
    ccon_n_node_address* address = ccon_n_create_address(char_addresses,
                                                         integer_addresses,
                                                         char_address_count,
                                                         integer_address_count);
    ASSERT_NE(address, nullptr);


    ccon_n_node_single_server* single_server = ccon_n_create_single_server(address, &TestFunctionServe);
    ASSERT_NE(single_server, nullptr);

    ccon_n_node_single_server* single_server_two = ccon_n_copy_single_server(single_server);
    ASSERT_NE(single_server_two, nullptr);

    int result = ccon_n_delete_single_server(&single_server);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(single_server, nullptr);

    int result_two = ccon_n_delete_single_server(&single_server_two);
    ASSERT_EQ(result_two, 0);
    ASSERT_EQ(single_server_two, nullptr);

    free(integer_addresses);
    free(char_addresses[0]);
    free(char_addresses[1]);
    free(char_addresses[2]);
    free(char_addresses);
}

TEST_F(SingleServerTest, SingleServerNULLCreationAndDeletion) {
    ccon_n_node_single_server* single_server = ccon_n_create_single_server(nullptr, nullptr);
    ASSERT_NE(single_server, nullptr);

    int result = ccon_n_delete_single_server(&single_server);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(single_server, nullptr);
}

TEST_F(SingleServerTest, SingleServerCreationAndInvocation) {
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
    ccon_n_node_address* address = ccon_n_create_address(char_addresses,
                                                         integer_addresses,
                                                         char_address_count,
                                                         integer_address_count);
    ASSERT_NE(address, nullptr);

    ccon_n_node_single_server* single_server = ccon_n_create_single_server(address, &TestFunctionServe);
    ASSERT_NE(single_server, nullptr);

    int result = 0;
    int* serve_return = (int*) ccon_n_invoke_server(single_server, &result, nullptr);
    ASSERT_EQ(result, 0);
    ASSERT_NE(serve_return, nullptr);
    ASSERT_EQ(*serve_return, 1);

    free(serve_return);

    int del_result = ccon_n_delete_single_server(&single_server);
    ASSERT_EQ(del_result, 0);
    ASSERT_EQ(single_server, nullptr);

    free(integer_addresses);
    free(char_addresses[0]);
    free(char_addresses[1]);
    free(char_addresses[2]);
    free(char_addresses);
}
