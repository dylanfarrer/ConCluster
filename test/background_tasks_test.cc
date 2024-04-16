#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include "../include/node/background_tasks.h"
}

class BackgroundTasksTest : public ::testing::Test {
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

// Test background_tasks creation and deletion
TEST_F(BackgroundTasksTest, BackgroundTasksCreationAndDeletion) {
    // create components
    Action* actions_array = (Action*) malloc(3 * sizeof(Action));
    actions_array[0] = &TestFunctionOne;
    actions_array[1] = &TestFunctionTwo;
    actions_array[2] = &TestFunctionThree;

    int action_count = 3;

    // create actions struct and assert success
    node_actions* actions = create_actions(actions_array, action_count);
    ASSERT_NE(actions, nullptr);
    
    node_background_tasks* background_tasks = create_background_tasks(actions, &TestFunctionSchedule);
    ASSERT_NE(background_tasks, nullptr);
    
    int result = delete_background_tasks(background_tasks);
    ASSERT_EQ(result, 0);

    free(actions_array);
}

TEST_F(BackgroundTasksTest, BackgroundTasksCopy) {
    // create components
    Action* actions_array = (Action*) malloc(3 * sizeof(Action));
    actions_array[0] = &TestFunctionOne;
    actions_array[1] = &TestFunctionTwo;
    actions_array[2] = &TestFunctionThree;

    int action_count = 3;

    // create actions struct and assert success
    node_actions* actions = create_actions(actions_array, action_count);
    ASSERT_NE(actions, nullptr);
    
    node_background_tasks* background_tasks = create_background_tasks(actions, &TestFunctionSchedule);
    ASSERT_NE(background_tasks, nullptr);

    node_background_tasks* background_tasks_two = copy_background_tasks(background_tasks);
    ASSERT_NE(background_tasks_two, nullptr);
    
    int result = delete_background_tasks(background_tasks);
    ASSERT_EQ(result, 0);

    int result_two = delete_background_tasks(background_tasks_two);
    ASSERT_EQ(result_two, 0);

    free(actions_array);
}

TEST_F(BackgroundTasksTest, BackgroundNULLTasksCreationAndDeletion) {
    node_background_tasks* background_tasks = create_background_tasks(nullptr, nullptr);
    ASSERT_NE(background_tasks, nullptr);
    
    int result = delete_background_tasks(background_tasks);
    ASSERT_EQ(result, 0);
}
