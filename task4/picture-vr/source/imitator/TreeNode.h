#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "Matrix.h"

using vec3 = std::array<float, 3>;
using vec4 = std::array<float, 4>;

struct StateVector;

class TreeNode {
public:
    // array of pointers on child nodes
    TreeNode* *children = nullptr;

    struct DataNode {
        int id_type;
        int id_name;

        vec3 scale;
        vec3 rotation; // Euler angles
        vec3 move;

        int id_texture;
        vec4 color;

        DataNode() : id_type(0), id_name(0),
                scale({1.f, 1.f, 1.f}), rotation({0.f, 0.f, 0.f}), move({0.f, 0.f, 0.f}),
                id_texture(0), color({0.f, 0.f, 0.f, 0.f}) {
        }
        DataNode(int id_type, int id_name) : DataNode() {
            this->id_type = id_type;
            this->id_name = id_name;
        }
        DataNode(int id_type, int id_name, vec3 scale, vec3 rotation, vec3 move)
        : DataNode(id_type, id_name) {
            this->scale = scale;
            this->rotation = rotation;
            this->move = move;
        }
        DataNode(int id_type, int id_name, vec3 scale, vec3 rotation, vec3 move, int id_texture, vec4 color)
        : DataNode(id_type, id_name, scale, rotation, move) {
            this->id_texture = id_texture;
            this->color = color;
        }
    } data{};
protected:
    size_t children_buf_count = 0;
    size_t children_count = 0;

public:
    TreeNode() = default;
    TreeNode(const DataNode& new_data, size_t new_children_count);

    TreeNode& operator=(const TreeNode& other);

    void add(TreeNode* child);
    virtual void routine() { /* implemented in derived classes */ }

//    vec3 get_scale() const;
//    vec3 get_rotation() const;
//    vec3 get_move() const;
//    void set_rotation(vec3 rotation);

    size_t get_children_count() const;

    StateVector get_state_vector() const;

    virtual ~TreeNode();

//protected:
//    Matrix matrix_from_rotation() const;
//    static vec3 rotation_from_matrix(const Matrix& matrix) ;
};

struct StateVector {
    int id_type;
    int id_name;
    vec3 scale;
    vec3 rotation;
    vec3 move;

    StateVector() = delete;
    explicit StateVector(TreeNode::DataNode data) :
        id_type(data.id_type),
        id_name(data.id_name),
        scale(data.scale),
        rotation(data.rotation),
        move(data.move) {
    }
};

struct TreeNodeHeader {
    TreeNode* root;
    int32_t id_frame;
    int32_t time;

    TreeNodeHeader(TreeNode* root, int32_t id_frame, int32_t time)
    : root(root), id_frame(id_frame), time(time) {
    }
    TreeNodeHeader() = default;
};
