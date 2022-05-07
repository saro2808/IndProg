project(serializer)

add_library(serializer_lib Serializer.cpp)

add_executable(serializer_test main.cpp)

target_link_libraries(serializer_lib tree_node_lib)

target_link_libraries(serializer_test serializer_lib gtest_main gtest Threads::Threads)

include(GoogleTest)
gtest_discover_tests(serializer_test)
