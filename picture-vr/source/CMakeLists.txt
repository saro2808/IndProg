cmake_minimum_required(VERSION 3.12)

project(source)

find_package (Threads REQUIRED)
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_subdirectory(client)
add_subdirectory(imitator)
add_subdirectory(serializer)
add_subdirectory(server)