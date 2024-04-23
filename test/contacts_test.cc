#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include "../include/node/contacts.h"
}

class ContactsTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test contacts creation and deletion
TEST_F(ContactsTest, ContactsCreationAndDeletion) {
    // create components
    // create several address structs
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

    ccon_n_node_address* address_one = ccon_n_create_address(char_addresses,
                                           integer_addresses,
                                           char_address_count,
                                           integer_address_count);
    ASSERT_NE(address_one, nullptr);

    ccon_n_node_address* address_two = ccon_n_create_address(char_addresses,
                                               integer_addresses,
                                               char_address_count,
                                               integer_address_count);
    ASSERT_NE(address_two, nullptr);


    ccon_n_node_address** address_array = (ccon_n_node_address**) malloc(sizeof(ccon_n_node_address*) * 2);
    address_array[0] = address_one;
    address_array[1] = address_two;

    int address_count = 2;

    node_contacts* contacts = create_contacts(address_array, address_count);
    ASSERT_NE(contacts, nullptr);

    int result = delete_contacts(contacts);
    ASSERT_EQ(result, 0);

    free(address_array);
    free(integer_addresses);
    free(char_addresses[0]);
    free(char_addresses[1]);
    free(char_addresses[2]);
    free(char_addresses);
}

TEST_F(ContactsTest, ContactsCopy) {
    // create components
    // create several address structs
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

    ccon_n_node_address* address_one = ccon_n_create_address(char_addresses,
                                           integer_addresses,
                                           char_address_count,
                                           integer_address_count);
    ASSERT_NE(address_one, nullptr);

    ccon_n_node_address* address_two = ccon_n_create_address(char_addresses,
                                               integer_addresses,
                                               char_address_count,
                                               integer_address_count);
    ASSERT_NE(address_two, nullptr);


    ccon_n_node_address** address_array = (ccon_n_node_address**) malloc(sizeof(ccon_n_node_address*) * 2);
    address_array[0] = address_one;
    address_array[1] = address_two;

    int address_count = 2;

    node_contacts* contacts = create_contacts(address_array, address_count);
    ASSERT_NE(contacts, nullptr);

    node_contacts* contacts_two = copy_contacts(contacts);
    ASSERT_NE(contacts_two, nullptr);

    int result = delete_contacts(contacts);
    ASSERT_EQ(result, 0);

    int result_two = delete_contacts(contacts_two);
    ASSERT_EQ(result_two, 0);

    free(address_array);
    free(integer_addresses);
    free(char_addresses[0]);
    free(char_addresses[1]);
    free(char_addresses[2]);
    free(char_addresses);
}

TEST_F(ContactsTest, ContactsNULLCreationAndDeletion) {
    node_contacts* contacts = create_contacts(nullptr, 0);
    ASSERT_NE(contacts, nullptr);

    int result = delete_contacts(contacts);
    ASSERT_EQ(result, 0);
}
