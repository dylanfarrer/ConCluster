#include <gtest/gtest.h>
#include <thread>
#include <chrono>

extern "C" {
    #include "../include/socket_handler.h"
}

class SocketTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

char* function1() {
    return (char*)"Hello, World!";
}

char* function2() {
    return (char*)"Hello, World, Two!";
}

TEST_F(SocketTest, SendAndReceiveOnSocket) {
    const char* ip = "127.0.0.1";
    int port = 8080;
    const char* message_one = (char*)"endpoint1";
    const char* message_two = (char*)"endpoint2";
    const char* message_three = (char*)"endpoint3";

    std::thread server_thread([&]() {
        char* endpoints[] = {(char*)"endpoint1", (char*)"endpoint2"};
        FunctionPtr functions[] = {function1, function2};
        int result = listen_on_socket(port, endpoints, functions, 2);
        EXPECT_EQ(result, 0);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    char* received_message_one = send_and_recieve_on_socket(ip, port, message_one);
    ASSERT_STREQ(received_message_one, (char*)"Hello, World!");
    free(received_message_one);
    
    char* received_message_two = send_and_recieve_on_socket(ip, port, message_two);
    ASSERT_STREQ(received_message_two, (char*)"Hello, World, Two!");
    free(received_message_two);

    char* received_message_three = send_and_recieve_on_socket(ip, port, message_three);
    ASSERT_STREQ(received_message_three, (char*)"ERR");
    free(received_message_three);

    ASSERT_EQ(send_kill_message(ip, port), 0);
 
    server_thread.join();
}
