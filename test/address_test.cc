#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include "../include/node/address.h"
}

class AddressTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test address creation and deletion
TEST_F(AddressTest, AddressCreationAndDeletion) {
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
    ccon_n_node_address* address = ccon_n_create_address(char_addresses,
                                                         integer_addresses,
                                                         char_address_count,
                                                         integer_address_count);
    ASSERT_NE(address, nullptr);

    int result = ccon_n_delete_address(address);
    ASSERT_EQ(result, 0);

    free(integer_addresses);
    free(char_addresses[0]);
    free(char_addresses[1]);
    free(char_addresses[2]);
    free(char_addresses);
}

TEST_F(AddressTest, AddressCopy) {
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
    ccon_n_node_address* address = ccon_n_create_address(char_addresses,
                                                         integer_addresses,
                                                         char_address_count,
                                                         integer_address_count);
    ASSERT_NE(address, nullptr);

    ccon_n_node_address* address_two = ccon_n_copy_address(address);
    ASSERT_NE(address_two, nullptr);

    int result = ccon_n_delete_address(address);
    ASSERT_EQ(result, 0);

    int result_two = ccon_n_delete_address(address_two);
    ASSERT_EQ(result_two, 0);

    free(integer_addresses);
    free(char_addresses[0]);
    free(char_addresses[1]);
    free(char_addresses[2]);
    free(char_addresses);
}

TEST_F(AddressTest, AddressNULLCreationAndDeletion) {
    ccon_n_node_address* address = ccon_n_create_address(nullptr, nullptr, 0, 0);
    ASSERT_NE(address, nullptr);

    int result = ccon_n_delete_address(address);
    ASSERT_EQ(result, 0);
}
