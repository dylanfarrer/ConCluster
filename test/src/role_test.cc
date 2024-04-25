#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include <concluster/cluster.h>
}

class RoleTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test role creation and deletion
TEST_F(RoleTest, RoleCreationAndDeletion) {
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

    int char_role_count = 3;
    int integer_role_count = 3;
    ccon_n_node_role* role = ccon_n_create_role(char_roles,
                                                integer_roles,
                                                char_role_count,
                                                integer_role_count);
    ASSERT_NE(role, nullptr);

    int result = ccon_n_delete_role(&role);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(role, nullptr);

    free(integer_roles);
    free(char_roles[0]);
    free(char_roles[1]);
    free(char_roles[2]);
    free(char_roles);
}

TEST_F(RoleTest, RoleCopy) {
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

    int char_role_count = 3;
    int integer_role_count = 3;
    ccon_n_node_role* role = ccon_n_create_role(char_roles,
                                                 integer_roles,
                                                 char_role_count,
                                                 integer_role_count);
    ASSERT_NE(role, nullptr);

    ccon_n_node_role* role_two = ccon_n_copy_role(role);
    ASSERT_NE(role_two, nullptr);

    int result = ccon_n_delete_role(&role);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(role, nullptr);

    int result_two = ccon_n_delete_role(&role_two);
    ASSERT_EQ(result_two, 0);
    ASSERT_EQ(role_two, nullptr);

    free(integer_roles);
    free(char_roles[0]);
    free(char_roles[1]);
    free(char_roles[2]);
    free(char_roles);
}

TEST_F(RoleTest, RoleNULLCreationAndDeletion) {
    ccon_n_node_role* role = ccon_n_create_role(nullptr,
                                  nullptr,
                                  0,
                                  0);
    ASSERT_NE(role, nullptr);

    int result = ccon_n_delete_role(&role);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(role, nullptr);
}
