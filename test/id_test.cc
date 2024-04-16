#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include "../include/node/id.h"
}

class IdTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test id creation and deletion
TEST_F(IdTest, IdCreationAndDeletion) {
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

    int char_id_count = 3;
    int integer_id_count = 3;
    node_id* id = create_id(char_ids,
                            integer_ids,
                            char_id_count,
                            integer_id_count);
    ASSERT_NE(id, nullptr);

    int result = delete_id(id);
    ASSERT_EQ(result, 0);

    free(integer_ids);
    free(char_ids[0]);
    free(char_ids[1]);
    free(char_ids[2]);
    free(char_ids);
}

TEST_F(IdTest, IdCopy) {
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

    int char_id_count = 3;
    int integer_id_count = 3;
    node_id* id = create_id(char_ids,
                            integer_ids,
                            char_id_count,
                            integer_id_count);
    ASSERT_NE(id, nullptr);

    node_id* id_two = copy_id(id);
    ASSERT_NE(id_two, nullptr);

    int result = delete_id(id);
    ASSERT_EQ(result, 0);

    int result_two = delete_id(id_two);
    ASSERT_EQ(result_two, 0);

    free(integer_ids);
    free(char_ids[0]);
    free(char_ids[1]);
    free(char_ids[2]);
    free(char_ids);
}

TEST_F(IdTest, IdNULLCreationAndDeletion) {
    node_id* id = create_id(nullptr,
                            nullptr,
                            0,
                            0);
    ASSERT_NE(id, nullptr);

    int result = delete_id(id);
    ASSERT_EQ(result, 0);
}
