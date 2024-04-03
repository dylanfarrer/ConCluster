#include <gtest/gtest.h>
#include <thread>
#include <chrono>

extern "C" {
    #include "../include/socket_handler.h"
}

// Test fixture for socket methods
class SocketTest : public ::testing::Test {
protected:
    // Set up before each test
    void SetUp() override {
        // Initialize any common variables or objects
    }

    // Tear down after each test
    void TearDown() override {
        // Clean up any allocated resources
    }
};

char* function1() {
    return (char*)"Hello, World!";
}

char* function2() {
    return (char*)"Hello, World, Two!";
}

// Test case for create_listener_socket function
TEST_F(SocketTest, CreateListenerSocket) {
    int port = 8080;
    int listener_socket = create_listener_socket(port);
    ASSERT_TRUE(listener_socket);
    close(listener_socket);
}

// Test case for create_sender_socket function
TEST_F(SocketTest, CreateSenderSocket) {
    int sender_socket = create_sender_socket();
    ASSERT_TRUE(sender_socket); // Check if sender socket creation was successful
    close(sender_socket); // Close the sender socket
}

// Test case for send_and_receive_on_socket function
TEST_F(SocketTest, SendAndReceiveOnSocket) {
    const char* ip = "127.0.0.1"; // Example IP address
    int port = 8080;
    const char* message_one = (char*)"endpoint1";
    const char* message_two = (char*)"endpoint2";
    const char* message_three = (char*)"endpoint3";

    // Start the server in a separate thread
    std::thread server_thread([&]() {
        int listener_socket = create_listener_socket(port); // Create a listener socket
        ASSERT_TRUE(listener_socket); // Check if listener socket creation was successful
        char* endpoints[] = {(char*)"endpoint1", (char*)"endpoint2"};
        FunctionPtr functions[] = {function1, function2}; // Example function pointers
        int result = listen_on_socket(listener_socket, endpoints, functions, 2);
        EXPECT_EQ(result, 0); // Check if listening on the socket was successful
        close(listener_socket); // Close the listener socket
    });

    // Sleep for a short time to allow the server to start
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Create a sender socket and send a message
    int sender_socket = create_sender_socket();
    ASSERT_TRUE(sender_socket); 
    char* received_message_one = send_and_recieve_on_socket(sender_socket, ip, port, message_one);
    ASSERT_STREQ(received_message_one, (char*)"Hello, World!");
    free(received_message_one);
    
    sender_socket = create_sender_socket();
    ASSERT_TRUE(sender_socket); 
    char* received_message_two = send_and_recieve_on_socket(sender_socket, ip, port, message_two);
    ASSERT_STREQ(received_message_two, (char*)"Hello, World, Two!");
    free(received_message_two);

    sender_socket = create_sender_socket();
    ASSERT_TRUE(sender_socket); 
    char* received_message_three = send_and_recieve_on_socket(sender_socket, ip, port, message_three);
    ASSERT_STREQ(received_message_three, (char*)"ERR");
    free(received_message_three);

    sender_socket = create_sender_socket();
    ASSERT_TRUE(sender_socket); 
    ASSERT_EQ(send_kill_message(sender_socket, ip, port), 0);
 
    server_thread.join();
}
