cmake_minimum_required(VERSION 3.10)

project(vr)

set(CMAKE_CXX_STANDARD 14)

include_directories(. ../server ../server/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(tree_node_lib
        TreeNode.cpp
        Matrix.cpp)

add_executable(vr
        main.cpp
        Imitator.cpp
        Imitator.h
        Matrix.cpp
        Matrix.h
        TreeNode.cpp
        TreeNode.h
        TreeLeaves.cpp
        TreeLeaves.h)

target_link_libraries(vr
	server_lib)
