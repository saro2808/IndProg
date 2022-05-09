#include "TreeNode.h"
#include "Matrix.h"

#include <cmath>
#include <cstddef>
#include <stdexcept>

TreeNode::TreeNode(const DataNode& new_data, size_t new_children_buf_count)
        : data(new_data), children_buf_count(new_children_buf_count) {
    if (children_buf_count > 0) {
        children = new TreeNode *[children_buf_count];
        for (int i = 0; i < children_buf_count; ++i) {
            children[i] = nullptr;
        }
    }
}

TreeNode::~TreeNode() {
    if (children_buf_count > 0) {
        delete[] children;
        children_buf_count = 0;
    }
}

void TreeNode::add(TreeNode* new_node) {
    if (new_node == nullptr) {
        throw std::invalid_argument("Trying to add nullptr as new child of TreeNode\n");
    }
    if (children_buf_count == 0) {
        children = new TreeNode*[1];
        children[0] = new_node;
        children_buf_count = 1;
        children_count = 1;
        return;
    }
    if (children_count == children_buf_count) {
        children_buf_count = 2 * (children_count + 1);
        auto* *new_buf = new TreeNode*[children_buf_count];
        for (size_t i = 0; i < children_count; ++i) {
            new_buf[i] = children[i];
        }
        for (size_t i = children_count; i < children_buf_count; ++i) {
            new_buf[i] = nullptr;
        }
        delete[] children;
        children = new_buf;
    }
    children[children_count++] = new_node;
}

//vec3 TreeNode::get_scale() const {
//    return data.scale;
//}
//
//vec3 TreeNode::get_rotation() const {
//    return data.rotation;
//}
//
//vec3 TreeNode::get_move() const {
//    return data.move;
//}
//
//void TreeNode::set_rotation(vec3 rotation) {
//    data.rotation = rotation;
//}

size_t TreeNode::get_children_count() const {
    return children_count;
}

StateVector TreeNode::get_state_vector() const {
    return StateVector(data);
}

//Matrix TreeNode::matrix_from_rotation() const {
//    auto cos_x = static_cast<float>(cos(data.rotation[0]));
//    auto sin_x = static_cast<float>(sin(data.rotation[0]));
//    Matrix R_x_psi(vec9({
//                                1.f,    0.f,    0.f,
//                                0.f,    cos_x,  -sin_x,
//                                0.f,    sin_x,  cos_x
//                        }));
//    cos_x = static_cast<float>(cos(data.rotation[1]));
//    sin_x = static_cast<float>(sin(data.rotation[1]));
//    Matrix R_y_theta(vec9({
//                                  cos_x,  0.f,    sin_x,
//                                  0.f,    1.f,    0.f,
//                                  -sin_x, 0.f,    cos_x
//                          }));
//    cos_x = static_cast<float>(cos(data.rotation[2]));
//    sin_x = static_cast<float>(sin(data.rotation[2]));
//    Matrix R_z_phi(vec9({
//                                cos_x,  -sin_x, 0.f,
//                                sin_x,  cos_x,  0.f,
//                                0.f,    0.f,    1.f
//                        }));
//    return R_z_phi * R_y_theta * R_x_psi;
//}

//vec3 TreeNode::rotation_from_matrix(const Matrix& matrix) {
//    vec3 rotation;
//    rotation[0] = static_cast<float>(std::atan2(matrix[2][1], matrix[2][2]));
//    rotation[1] = static_cast<float>(std::atan2(-matrix[2][0], std::sqrt(matrix[2][1]*matrix[2][1] + matrix[2][2]*matrix[2][2])));
//    rotation[2] = static_cast<float>(std::atan2(matrix[1][0], matrix[0][0]));
//    return rotation;
//}

TreeNode &TreeNode::operator=(const TreeNode &other) {
    if (this == &other) {
        return *this;
    }
    children_count = other.children_count;
    children_buf_count = other.children_buf_count;
    data = other.data;
    if (children_buf_count > 0) {
        children = new TreeNode*[children_buf_count];
    }
    for (int i = 0; i < children_count; ++i) {
        children[i] = other.children[i];
    }
    return *this;
}

