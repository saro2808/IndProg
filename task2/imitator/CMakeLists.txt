cmake_minimum_required(VERSION 3.12)

project(vr)

set(CMAKE_CXX_STANDARD 14)

include_directories(. ../server ../server/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_library(tree_node_lib
	TreeNode.cpp
	Matrix.cpp)

add_executable(vr
	main.cpp
	Imitator.cpp	Imitator.h
	Matrix.cpp	Matrix.h
	TreeNode.cpp	TreeNode.h
	TreeLeaves.cpp	TreeLeaves.h)

add_executable(hello_test
	unit_test.cpp
	Car.cpp		Car.h
	Imitator.cpp	Imitator.h
	Matrix.cpp	Matrix.h
	TreeNode.h	TreeNode.cpp
	TreeLeaves.cpp	TreeLeaves.h)

include(GoogleTest)
gtest_discover_tests(hello_test)

#target_link_libraries(vr
#	server_lib)

target_link_libraries(hello_test
	#server_lib
	gtest_main gtest)
