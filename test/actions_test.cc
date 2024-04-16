#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include "../include/node/actions.h"
}

class ActionsTest : public ::testing::Test {
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

// Test action creation and deletion
TEST_F(ActionsTest, ActionsCreationAndDeletion) {
    // create components
    Action* actions_array = (Action*) malloc(3 * sizeof(Action));
    actions_array[0] = &TestFunctionOne;
    actions_array[1] = &TestFunctionTwo;
    actions_array[2] = &TestFunctionThree;

    int action_count = 3;

    node_actions* actions = create_actions(actions_array, action_count);
    ASSERT_NE(actions, nullptr);

    int result = delete_actions(actions);
    ASSERT_EQ(result, 0);

    free(actions_array);
}

TEST_F(ActionsTest, ActionsCopy) {
    // create components
    Action* actions_array = (Action*) malloc(3 * sizeof(Action));
    actions_array[0] = &TestFunctionOne;
    actions_array[1] = &TestFunctionTwo;
    actions_array[2] = &TestFunctionThree;

    int action_count = 3;

    node_actions* actions = create_actions(actions_array, action_count);
    ASSERT_NE(actions, nullptr);

    node_actions* actions_two = copy_actions(actions);
    ASSERT_NE(actions_two, nullptr);

    int result = delete_actions(actions);
    ASSERT_EQ(result, 0);

    int result_two = delete_actions(actions_two);
    ASSERT_EQ(result_two, 0);

    free(actions_array);
}


TEST_F(ActionsTest, ActionsNULLCreationAndDeletion) {
    node_actions* actions = create_actions(nullptr, 0);
    ASSERT_NE(actions, nullptr);

    int result = delete_actions(actions);
    ASSERT_EQ(result, 0);
}
