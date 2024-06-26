cmake_minimum_required(VERSION 3.22)
project(ConCluster)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-deprecated-declarations") # -address sanitize if needed
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-declarations") # -address sanitize if needed
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}") # -address sanitize if needed

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(GoogleTest)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    googletest
    DOWNLOAD_EXTRACT_TIMESTAMP true
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

find_library(CONCLUSTER_LIB concluster PATHS /usr/local/lib)
include_directories(/usr/local/include/)

enable_testing()

file(GLOB_RECURSE TEST_SOURCES "src/*.cc")
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests gtest_main ${CONCLUSTER_LIB})
target_include_directories(tests PRIVATE include Threads::Threads)
gtest_discover_tests(tests)
