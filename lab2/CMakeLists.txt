cmake_minimum_required(VERSION 3.10)
project(gtest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp Four.cpp)


enable_testing()
add_executable(test2 test2.cpp  Four.cpp)
target_link_libraries(test2 ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND test2)