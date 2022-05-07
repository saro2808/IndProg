#ifndef SERIALIZER_SERIALIZER_H
#define SERIALIZER_SERIALIZER_H

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <vector>
#include <random>

#include "include/nlohmann/json.hpp"
#include "../imitator/TreeNode.h"


class Serializer { // inherited

public:
    //whole information will write in file_name
    static int serialize(const std::string& file_name, const TreeNodeHeader& scene);
    //whole information will write in root_node
    static int unserialize(const std::string& file_name, TreeNodeHeader& root_node);
    //whole information will return to string
    static std::string serialize_to_string(const TreeNodeHeader& scene);
    //whole information will return to TreeNode
    static TreeNodeHeader* unserialize_from_string(const std::string& serialized_string);

private:
    static int serialize_json_from_node(const TreeNode* root, nlohmann::json& j);
    static int serialize_json_from_scene(const TreeNodeHeader* scene, nlohmann::json& j);

    static int unserialize_scene_from_json(const nlohmann::json& j, TreeNodeHeader& scene);
    static int unserialize_node_from_json(const nlohmann::json& j, TreeNode& node);
};

#endif // SERIALIZER_SERIALIZER_H
