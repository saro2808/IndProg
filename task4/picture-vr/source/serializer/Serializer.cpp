#include "Serializer.h"

int Serializer::serialize_json_from_scene(const TreeNodeHeader* scene, nlohmann::json& j) {
    if (scene == nullptr) return 1;

    j["id_frame"] = scene->id_frame;
    j["time"] = scene->time;
    serialize_json_from_node(scene->root, j["root"]);
    return 0;
}

 int Serializer::serialize_json_from_node(const TreeNode* root, nlohmann::json& j) {
     if (root == nullptr) return 1;

     j["data"]["id_type"] = root->data.id_type;
     j["data"]["id_name"] = root->data.id_name;
     j["data"]["scale"] = root->data.scale;
     j["data"]["rotation"] = root->data.rotation;
     j["data"]["move"] = root->data.move;
     j["data"]["id_texture"] = root->data.id_texture;
     j["data"]["color"] = root->data.color;

     std::vector<nlohmann::json> children;
     if (root->children[0]) {
         for (int i = 0; root->children[i]; ++i) {
             nlohmann::json j_child_node;
             TreeNode *child = root->children[i];
             serialize_json_from_node(child, j_child_node);
             children.push_back(j_child_node);
         }
         j["children"] = children;
     }
     return 0;
 }

int Serializer::unserialize_scene_from_json(const nlohmann::json& j, TreeNodeHeader& scene) {
    scene.time = j["time"].get<int32_t>();
    scene.id_frame = j["id_frame"].get<int32_t>();
    scene.root = new TreeNode;
    unserialize_node_from_json(j["root"], *scene.root);
    return 1;
}

int Serializer::unserialize_node_from_json(const nlohmann::json& j, TreeNode& node) {
    int i = 0;
    node.data.color = j["data"]["color"].get<std::array<float, 4>>();
    node.data.rotation = j["data"]["rotation"].get<std::array<float, 3>>();
    node.data.scale = j["data"]["scale"].get<std::array<float, 3>>();
    node.data.move = j["data"]["move"].get<std::array<float, 3>>();
    node.data.id_texture = j["data"]["id_texture"].get<int32_t>();
    node.data.id_name = j["data"]["id_name"].get<int32_t>();
    node.data.id_type = j["data"]["id_type"].get<int32_t>();

    if (j.find("children") != j.end()) {
        nlohmann::json a = j["children"].get<nlohmann::json>();

        node.children = new TreeNode*[a.size()+1];
        node.children[a.size()] = nullptr;
        for (nlohmann::json::iterator it = a.begin(); it != a.end(); ++it) {
            node.children[i] = new TreeNode;
            unserialize_node_from_json(*it, *node.children[i]);
            i++;
        }

    } else {
        node.children = new TreeNode*[1];
        node.children[0] = nullptr;
    }

    return 0;
}


int Serializer::serialize(const std::string& file_name, const TreeNodeHeader& scene) {
    int res;
    nlohmann::json  j;

    res = serialize_json_from_scene(&scene, j);
    if (res == 0) {
        std::ofstream f(file_name);

        if (!f) {
            std::cerr << "Unable to open output file\n" << std::endl;
            return -1;
        }
        f << std::setw(2) << j << std::endl;
    }
    return res;
}


int Serializer::unserialize(const std::string& file_name, TreeNodeHeader& scene) {
    nlohmann::json  j;
    std::ifstream f(file_name);

    if (!f) {
        std::cerr << "Unable to open input file\n" << std::endl;
        return -1;
    }

    f >> j;

    return unserialize_scene_from_json(j, scene);
}

std::string Serializer::serialize_to_string(const TreeNodeHeader& scene) {
    int res;
    nlohmann::json  j;

    res = serialize_json_from_scene(&scene, j);
    std::string serialized_string = j.dump();

    return serialized_string;
}

TreeNodeHeader* Serializer::unserialize_from_string(const std::string& serialized_string) {
    nlohmann::json  j = nlohmann::json::parse(serialized_string);
    TreeNodeHeader* scene = new TreeNodeHeader;
    int res = unserialize_scene_from_json(j, *scene);
    return scene;
}