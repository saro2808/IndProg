#pragma once

#include <cmath>

#include "TreeNode.h"
#include "Matrix.h"

class Car : public TreeNode {
public:
    static const int wheels_count = 4;

    Car() = delete;
    explicit Car(DataNode new_data);

    //void routine() override;

    ~Car() override;
//private:
//    void display(int obj_index, int iteration) const;
//    void display(int iteration) const;
};

