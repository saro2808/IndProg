cmake_minimum_required(VERSION 2.8)

project(client)

add_library(client client.cpp)

add_executable(main main.cpp)

target_link_libraries(main client)
