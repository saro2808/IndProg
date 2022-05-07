#pragma once

#include <vector>


#include "TreeLeaves.h"
#include "../server/server.h"

class Imitator {
private:
    TreeNode* root = nullptr;
    size_t objects_count = 0;

    //Server server;
public:
    Imitator();
    explicit Imitator(size_t objects_count);

    void process_data(std::vector<TreeLeaves>& tree_leaves_array);

    void add(TreeNode* object_ptr);
    void run(size_t seconds);

    std::vector<StateVector> state_vectors() const;

    size_t get_objects_count() const;

    ~Imitator();

private:
    void fill_state_vectors(TreeNode* node, std::vector<StateVector>& state_vectors) const;
};
