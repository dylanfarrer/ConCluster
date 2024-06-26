#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
    #include <concluster/cluster.h>
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
    int* returnInt = (int*)malloc(sizeof(int));
    if (returnInt != NULL) {
        *returnInt = 1;
    }
    return returnInt;
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
    ccon_n_node_actions* actions = ccon_n_create_actions(actions_array, action_count);
    ASSERT_NE(actions, nullptr);
    
    ccon_n_node_background_tasks* background_tasks = ccon_n_create_background_tasks(actions, &TestFunctionSchedule);
    ASSERT_NE(background_tasks, nullptr);
    
    int result = ccon_n_delete_background_tasks(&background_tasks);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(background_tasks, nullptr);

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
    ccon_n_node_actions* actions = ccon_n_create_actions(actions_array, action_count);
    ASSERT_NE(actions, nullptr);
    
    ccon_n_node_background_tasks* background_tasks = ccon_n_create_background_tasks(actions, &TestFunctionSchedule);
    ASSERT_NE(background_tasks, nullptr);

    ccon_n_node_background_tasks* background_tasks_two = ccon_n_copy_background_tasks(background_tasks);
    ASSERT_NE(background_tasks_two, nullptr);
    
    int result = ccon_n_delete_background_tasks(&background_tasks);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(background_tasks, nullptr);

    int result_two = ccon_n_delete_background_tasks(&background_tasks_two);
    ASSERT_EQ(result_two, 0);
    ASSERT_EQ(background_tasks_two, nullptr);

    free(actions_array);
}

TEST_F(BackgroundTasksTest, BackgroundNULLTasksCreationAndDeletion) {
    ccon_n_node_background_tasks* background_tasks = ccon_n_create_background_tasks(nullptr, nullptr);
    ASSERT_NE(background_tasks, nullptr);
    
    int result = ccon_n_delete_background_tasks(&background_tasks);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(background_tasks, nullptr);
}

TEST_F(BackgroundTasksTest, BackgroundTasksCreationAndInvocation) {
    // create components
    Action* actions_array = (Action*) malloc(3 * sizeof(Action));
    actions_array[0] = &TestFunctionOne;
    actions_array[1] = &TestFunctionTwo;
    actions_array[2] = &TestFunctionThree;

    int action_count = 3;

    // create actions struct and assert success
    ccon_n_node_actions* actions = ccon_n_create_actions(actions_array, action_count);
    ASSERT_NE(actions, nullptr);
    
    ccon_n_node_background_tasks* background_tasks = ccon_n_create_background_tasks(actions, &TestFunctionSchedule);
    ASSERT_NE(background_tasks, nullptr);

    int result = 0;
    int* return_schedule = (int*) ccon_n_invoke_scheduler(background_tasks, &result, nullptr);
    ASSERT_EQ(result, 0);
    ASSERT_NE(return_schedule, nullptr);
    ASSERT_EQ(*return_schedule, 1);

    free(return_schedule);
    
    int del_result = ccon_n_delete_background_tasks(&background_tasks);
    ASSERT_EQ(del_result, 0);
    ASSERT_EQ(background_tasks, nullptr);

    free(actions_array);
}
