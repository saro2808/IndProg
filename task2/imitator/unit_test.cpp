#include <gtest/gtest.h>

#include <iostream>
#include <cmath>

#include "TreeNode.h"
#include "Car.h"
#include "Imitator.h"

namespace {
    TEST(TreeNodeTest, SimpleTest) {
        TreeNode::DataNode data(0, 0);
        TreeNode root(data, 0);
        for (int i = 0; i < 3; ++i) {
            root.add(new TreeNode);
        }

        EXPECT_EQ(3, root.get_children_count());
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(0, root.children[i]->get_children_count());
        }
        std::cout << "SimpleTest successfully finished\n";
    }

    TEST(ImitatorTest, DefaultConstructorTest) {
        Imitator imitator;

        vec3 scale = { 1.f, 1.f, 1.f };
        vec3 rotation = { 0.f, 0.f, static_cast<float>(M_PI) / 4 };
        vec3 move = { 0.f, 0.f, 0.f };

        Car car(TreeNode::DataNode(
                1,
                0,
                scale,
                rotation,
                move
        ));

        imitator.add(&car);

        EXPECT_EQ(1, imitator.get_objects_count());

        std::cout << "DefaultConstructorTest successfully finished\n";
    }

    TEST(ImitatorTest, OneArgConstructorTest) {
        Imitator imitator(3);

        vec3 scale = { 1.f, 1.f, 1.f };
        vec3 rotation = { 0.f, 0.f, static_cast<float>(M_PI) / 4 };
        vec3 move = { 0.f, 0.f, 0.f };

        Car car1(TreeNode::DataNode(
                1,
                0,
                scale,
                rotation,
                move
        ));

        Car car2(TreeNode::DataNode(
                1,
                1,
                scale,
                rotation,
                move
        ));

        Car car3(TreeNode::DataNode(
                1,
                2,
                scale,
                rotation,
                move
        ));

        imitator.add(&car1);
        imitator.add(&car2);
        imitator.add(&car2);

        EXPECT_EQ(3, imitator.get_objects_count());

        std::cout << "OneArgConstructorTest successfully finished\n";
    }

    TEST(ImitatorTest, TreeStructureTest) {
        Imitator imitator(2);

        vec3 scale = { 1.f, 1.f, 1.f };
        vec3 rotation = { 0.f, 0.f, static_cast<float>(M_PI) / 4 };
        vec3 move = { 0.f, 0.f, 0.f };

        Car car1(TreeNode::DataNode(
                1,
                0,
                scale,
                rotation,
                move
        ));

        Car car2(TreeNode::DataNode(
                1,
                1,
                scale,
                rotation,
                move
        ));

        Car car3(TreeNode::DataNode(
                1,
                2,
                scale,
                rotation,
                move
        ));

        imitator.add(&car1);
        imitator.add(&car2);
        imitator.add(&car3);

        std::vector<StateVector> svt = imitator.state_vectors();
//	for (auto sv : svt) {
//		std::cout << sv.id_type << " ";
//	}

        EXPECT_EQ(3, imitator.get_objects_count());

        EXPECT_EQ(0, svt[0].id_type);
        EXPECT_EQ(0, svt[0].id_name);
        for (int i = 0; i < imitator.get_objects_count(); ++i) {
            EXPECT_EQ(1, svt[1 + i * 5].id_type);
            EXPECT_EQ(i, svt[1 + i * 5].id_name);
        }
        for (int i = 0; i < imitator.get_objects_count(); ++i) {
            for (int j = 0; j < 4; ++j) {
                int index = 1 + i * 5 + 1 + j;
                EXPECT_EQ(2, svt[index].id_type);
                EXPECT_EQ(j, svt[index].id_name);
            }
        }

        std::cout << "TreeStructureTest successfully finished\n";
    }
}
