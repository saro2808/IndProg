project(server)

add_library(server_lib server.cpp)

add_executable(server_test main.cpp)

add_executable(server_unit_test unit_test.cpp)

target_link_libraries(server_lib serializer_lib)

target_link_libraries(server_test server_lib)

target_link_libraries(server_unit_test server_lib gtest_main gtest Threads::Threads)

include(GoogleTest)
gtest_discover_tests(server_unit_test)
