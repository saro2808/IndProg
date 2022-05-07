#pragma once

#include <cmath>
#include <vector>

#include "TreeNode.h"
#include "Matrix.h"

const auto pi = static_cast<float>(M_PI);
const float radian_to_degree = 180.f / pi;

const int tree_leave_id_type = 1;

class TreeLeaves : public TreeNode {
private:
    const std::vector<vec3> next_rotation = {
            {0.f, 0.f, 0.f},
            {0.05f, 0.05f, 0.f},
            {0.05f, 0.05f, 0.f},
            {0.1f, 0.1f, 0.f},
            {0.15f, 0.15f, 0.f},
            {0.15f, 0.15f, 0.05f},
            {0.15f, 0.15f, 0.1f},
            {0.15f, 0.15f, 0.1f},
            {0.15f, 0.15f, 0.1f},
            {0.15f, 0.15f, 0.1f},
            {0.2f, 0.2f, 0.1f},
            {0.2f, 0.2f, 0.1f},
            {0.3f, 0.3f, 0.1f},
            {0.2f, 0.2f, 0.1f},
            {0.2f, 0.2f, 0.05f},
            {0.15f, 0.15f, 0.05f},
            {0.15f, 0.15f, 0.05f},
            {0.15f, 0.15f, 0.05f},
            {0.15f, 0.15f, 0.05f},
            {0.15f, 0.15f, 0.05f},
            {0.10f, 0.10f, 0.f},
            {0.10f, 0.10f, 0.f},
            {0.05f, 0.05f, 0.f},
            {0.f, 0.f, 0.f},
            {0.f, 0.f, 0.f},
            {0.f, 0.f, 0.f},
            {0.f, 0.f, 0.f},
            {-0.05, -0.05, 0.f},
            {-0.05, -0.05, 0.f},
            {-0.1f, -0.1f, -0.05f},
            {-0.1f, -0.1f, -0.05f},
            {-0.15f, -0.15f, -0.05f},
            {-0.15f, -0.15f, -0.05f},
            {-0.15f, -0.15f, -0.05f},
            {-0.15f, -0.15f, -0.05f},
            {-0.15f, -0.15f, -0.05f},
            {-0.2f, -0.2f, -0.1f},
            {-0.2f, -0.2f, -0.1f},
            {-0.3f, -0.3f, -0.1f},
            {-0.3f, -0.3f, -0.1f},
            {-0.2f, -0.2f, -0.1f},
            {-0.2f, -0.2f, -0.1f},
            {-0.15f, -0.15f, -0.05f},
            {-0.15f, -0.15f, -0.05f},
            {-0.15f, -0.15f, -0.05f},
            {-0.15f, -0.15f, -0.05f},
            {-0.1f, -0.1f, 0.f},
            {-0.05, -0.05f, 0.f},
            {0.f, 0.f, 0.f},
            {0.f, 0.f, 0.f}
    };
    const uint cycle_length = next_rotation.size();
    uint next_index = 0;

public:
    TreeLeaves();
    explicit TreeLeaves(DataNode data);

    void routine() override;

    ~TreeLeaves() override = default;
};

