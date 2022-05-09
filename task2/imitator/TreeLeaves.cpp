#include <iostream>
#include <cmath>
#include "TreeLeaves.h"
#include "TreeNode.h"

TreeLeaves::TreeLeaves() : next_index(rand() % cycle_length) {
}

TreeLeaves::TreeLeaves(DataNode data) : TreeNode(data, 0) {
    next_index = rand() % cycle_length;
}

void TreeLeaves::routine() {
    for (int i = 0; i < 3; ++i) {
        data.rotation[i] += next_rotation[next_index][i];
    }
    next_index = ++next_index % cycle_length;
    std::cout << "next_index: " << next_index << ", id_type: " << data.id_type << ", id_name: " << data.id_name << ", data.rotation: "
    << data.rotation[0] << " " << data.rotation[1] << " " << data.rotation[2] << std::endl;
}