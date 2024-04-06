#include <gtest/gtest.h>
#include <pthread.h>

#define N_THREADS 10

extern "C" {
    #include "../include/thread_handler.h"
}

class ThreadTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

void* testFunction(void* pointer) {
    char* message = (char*) pointer;
    printf("%s\n", message);
    return NULL;
}

TEST_F(ThreadTest, RunAndJoinThreadTest) {
    pthread_t* threads[N_THREADS];

    for (int i = 0; i < N_THREADS; ++i) {
        threads[i] = run_thread(NULL, testFunction, (void*) (std::to_string(i)).c_str());
    }

    for(int j = 0; j < N_THREADS; ++j) {
        ASSERT_NE(threads[j], nullptr); 
    }

    for(int k = 0; k < N_THREADS; ++k) {
        join_thread(threads[k], NULL); 
    }
}
