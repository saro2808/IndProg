#include <iostream>
#include "include/nlohmann/json.hpp"
#include <cstdio>
#include "../imitator/TreeNode.h"
#include "Serializer.h"
#include "Tests_google.hpp"
//#include "Tests.hpp"
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    //SerilizerTests::TreeTest1();
    //SerilizerTests::TreeTest2();
    //SerilizerTests::TreeTest3();
    //SerilizerTests::TreeTest4();
}

