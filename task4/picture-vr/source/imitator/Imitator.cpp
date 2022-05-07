#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>

#include "Imitator.h"
#include "TreeNode.h"

Imitator::Imitator() {
    vec3 ones = { 1.f, 1.f, 1.f };
    vec3 zeros = { 0.f, 0.f, 0.f };
    root = new TreeNode(TreeNode::DataNode(0, 0, ones, ones, zeros), objects_count);
}

Imitator::Imitator(size_t objects_count) {
    vec3 ones = { 1.f, 1.f, 1.f };
    vec3 zeros = { 0.f, 0.f, 0.f };
    root = new TreeNode(TreeNode::DataNode(0, 0, ones, ones, zeros), objects_count);
}

void Imitator::process_data(std::vector<TreeLeaves>& tree_leaves_array) {
    std::ifstream scene_data("data.txt", std::ifstream::in);
    std::string line;
    while (getline(scene_data, line)) {
        std::string arr[10];
        uint end = line.find(' ');
        for (auto & i : arr) {
            i = line.substr(0, end);
            line = line.substr(end + 1, line.size());
            end = line.find(' ');
        }

        std::string name = arr[0];
        vec3 scale({std::stof(arr[1].substr(1, arr[1].size() - 1)),
                    std::stof(arr[2].substr(0, arr[2].size() - 1)),
                    std::stof(arr[3].substr(0, arr[3].size() - 1))});
        vec3 rotation({std::stof(arr[4].substr(1, arr[4].size() - 1)) * radian_to_degree,
                       std::stof(arr[5].substr(0, arr[5].size() - 1)) * radian_to_degree,
                       std::stof(arr[6].substr(0, arr[6].size() - 1)) * radian_to_degree});
        vec3 move({std::stof(arr[7].substr(1, arr[7].size() - 1)),
                   std::stof(arr[8].substr(0, arr[8].size() - 1)),
                   std::stof(arr[9].substr(0, arr[9].size() - 1))});

        const std::string real_name_prefix = "Stages_CyTree10_Leaf_Lod0";
        end = real_name_prefix.size();
        if (name.substr(0, end) == real_name_prefix) {
            int id_name = stoi(name.substr(end + 1, name.size()));
            tree_leaves_array.push_back(TreeLeaves({tree_leave_id_type, id_name, scale, rotation, move}));
        }
    }
    scene_data.close();
}

void Imitator::add(TreeNode* object_ptr) {
    if (object_ptr == nullptr) {
        throw std::invalid_argument("Trying to add nullptr as new object of Imitator\n");
    }
    root->add(object_ptr);
    ++objects_count;
}

void Imitator::run(size_t seconds) {
    const size_t delay = 40;
    const size_t thousand = 1000;
    const size_t million = thousand * thousand;

    std::vector<TreeLeaves> tree_leaves;
    process_data(tree_leaves);
    for (auto & tree_leave : tree_leaves) {
        add(&tree_leave);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = begin, previous_end, now;
    uint64_t delta;

    int iter = -1;
    do {
        std::cout << "iter " << ++iter << std::endl;
        std::cout << "timestamp: " << (end-begin).count() / million << std::endl;

        for (int i = 0; i < objects_count; ++i) {
            root->children[i]->routine();
        }

        previous_end = end;
        end = std::chrono::steady_clock::now();

        delta = (end - previous_end).count() / million;
        std::cout << "delta = " << delta << std::endl;

        now = std::chrono::steady_clock::now();
        int32_t time = static_cast<int32_t>((now - begin).count());

        //server.sendScene(TreeNodeHeader(root, iter, time));

	    //if (delta < delay) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        //}
    } while ((end - begin).count() / million < seconds * thousand);
}

std::vector<StateVector> Imitator::state_vectors() const {
    std::vector<StateVector> res;
    fill_state_vectors(root, res);
    return res;
}

void Imitator::fill_state_vectors(TreeNode *node, std::vector<StateVector>& state_vectors) const {
    state_vectors.push_back(node->get_state_vector());
    for (int i = 0; i < node->get_children_count(); ++i) {
        fill_state_vectors(node->children[i], state_vectors);
    }
}

size_t Imitator::get_objects_count() const {
	return objects_count;
}

Imitator::~Imitator() {
    delete root;
}
