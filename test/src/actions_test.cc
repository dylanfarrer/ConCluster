#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include <concluster/cluster.h>
}

class ActionsTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

static void* TestFunctionOne(void* value) {
    int* returnInt = (int*)malloc(sizeof(int));
    if (returnInt != NULL) {
        *returnInt = 1;
    }
    return returnInt;
}

static void* TestFunctionTwo(void* value) {
    int* returnInt = (int*)malloc(sizeof(int));
    if (returnInt != NULL) {
        *returnInt = 2;
    }
    return returnInt;
}

static void* TestFunctionThree(void* value) {
    int* returnInt = (int*)malloc(sizeof(int));
    if (returnInt != NULL) {
        *returnInt = 3;
    }
    return returnInt;
}

// Test action creation and deletion
TEST_F(ActionsTest, ActionsCreationAndDeletion) {
    // create components
    Action* actions_array = (Action*) malloc(3 * sizeof(Action));
    actions_array[0] = &TestFunctionOne;
    actions_array[1] = &TestFunctionTwo;
    actions_array[2] = &TestFunctionThree;

    int action_count = 3;

    ccon_n_node_actions* actions = ccon_n_create_actions(actions_array, action_count);
    ASSERT_NE(actions, nullptr);

    int result = ccon_n_delete_actions(&actions);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(actions, nullptr);

    free(actions_array);
}

TEST_F(ActionsTest, ActionsCopy) {
    // create components
    Action* actions_array = (Action*) malloc(3 * sizeof(Action));
    actions_array[0] = &TestFunctionOne;
    actions_array[1] = &TestFunctionTwo;
    actions_array[2] = &TestFunctionThree;

    int action_count = 3;

    ccon_n_node_actions* actions = ccon_n_create_actions(actions_array, action_count);
    ASSERT_NE(actions, nullptr);

    ccon_n_node_actions* actions_two = ccon_n_copy_actions(actions);
    ASSERT_NE(actions_two, nullptr);

    int result = ccon_n_delete_actions(&actions);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(actions, nullptr);

    int result_two = ccon_n_delete_actions(&actions_two);
    ASSERT_EQ(result_two, 0);
    ASSERT_EQ(actions_two, nullptr);

    free(actions_array);
}


TEST_F(ActionsTest, ActionsNULLCreationAndDeletion) {
    ccon_n_node_actions* actions = ccon_n_create_actions(nullptr, 0);
    ASSERT_NE(actions, nullptr);

    int result = ccon_n_delete_actions(&actions);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(actions, nullptr);
}

TEST_F(ActionsTest, ActionsCreationAndInvocation) {
    // create components
    Action* actions_array = (Action*) malloc(3 * sizeof(Action));
    actions_array[0] = &TestFunctionOne;
    actions_array[1] = &TestFunctionTwo;
    actions_array[2] = &TestFunctionThree;

    int action_count = 3;

    ccon_n_node_actions* actions = ccon_n_create_actions(actions_array, action_count);
    ASSERT_NE(actions, nullptr);

    int result = 0;

    int* return_one = (int*) ccon_n_invoke_action(actions, 0, &result, nullptr);
    ASSERT_EQ(result, 0);
    ASSERT_NE(return_one, nullptr);
    ASSERT_EQ(*return_one, 1);

    int* return_two = (int*) ccon_n_invoke_action(actions, 1, &result, nullptr);
    ASSERT_EQ(result, 0);
    ASSERT_NE(return_two, nullptr);
    ASSERT_EQ(*return_two, 2);

    int* return_three = (int*) ccon_n_invoke_action(actions, 2, &result, nullptr);
    ASSERT_EQ(result, 0);
    ASSERT_NE(return_three, nullptr);
    ASSERT_EQ(*return_three, 3);

    int del_result = ccon_n_delete_actions(&actions);
    ASSERT_EQ(del_result, 0);
    ASSERT_EQ(actions, nullptr);

    free(return_one);
    free(return_two);
    free(return_three);

    free(actions_array);
}

