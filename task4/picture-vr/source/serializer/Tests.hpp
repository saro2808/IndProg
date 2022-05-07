#include "Serializer.h"
#include <cassert>
#include <string>

#define N 10

TreeNode* newNode(int id_type, int id_name, int id_texture, std::array<float, 3> move, std::array<float, 4> color,
                  std::array<float, 3> rotation, std::array<float, 3> scale) {
    TreeNode* temp = new TreeNode;
    temp->data.move = move;
    temp->data.id_type = id_type;
    temp->data.id_name = id_name;
    temp->data.id_texture = id_texture;
    temp->data.color = color;
    temp->data.rotation = rotation;
    temp->data.scale = scale;
    temp->children = new TreeNode*[N];
    for (int i = 0; i < N; i++)
        temp->children[i] = NULL;
    return temp;
}

TreeNodeHeader* createDummyTree1()
{
    TreeNode* root = newNode(3, 2, 2, { 1.f, 1.f, 1.f }, { 1.f, 7.f, 1.f, 0.5f},
                             { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f });
    root->children[0] = newNode(3, 2, 4, { 1.f, 1.f, 1.f },{ 1.f, 1.f, 1.f, 0.5f},
                                { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f });

    TreeNodeHeader* scene = new TreeNodeHeader(root, 3, 4);
    return scene;
}

TreeNodeHeader* createDummyTree2() {
    TreeNode* root = newNode(3, 2, 2, { 1.f, 1.f, 1.f }, { 1.f, 7.f, 1.f, 0.5f},
                             { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f });

    TreeNodeHeader* scene = new TreeNodeHeader(root, 3, 7);
    return scene;
}

TreeNodeHeader* createDummyTree3()
{
    TreeNode* root = newNode(3, 2, 2, { 1.f, 1.f, 1.f }, { 1.f, 7.f, 1.f, 0.5f},
                             { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f });
    root->children[0] = newNode(3, 2, 4, { 1.f, 1.f, 1.f },{ 1.f, 1.f, 1.f, 0.5f},
                                { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f });
    root->children[1] = newNode(3, 5, 2, { 0.f, 0.f, 0.f },{ 1.f, 1.f, 1.f, 0.5f},
                                { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
    root->children[2] = newNode(7, 2, 2, { 0.f, 0.f, 0.f },{ 1.f, 3.f, 1.f, 0.5f},
                                { 0.f, 0.f, 0.f }, { 1.f, 1.f, 2.f });
    root->children[0]->children[0] = newNode(3, 9, 2, { 1.f, 1.f, 1.f },
                                             { 1.f, 1.f, 1.f, 0.5f},{ 1.f, 1.f, 1.f },
                                             { 4.f, 1.f, 1.f });
    root->children[0]->children[1] = newNode(3, 3, 2, { 0.f, 1.f, 0.f },
                                             { 1.f, 1.f, 3.f, 0.5f},{ 0.f, 0.f, 0.f }, { 1.f, 4.f, 1.f });

    TreeNodeHeader* scene = new TreeNodeHeader(root, 8, 4);
    return scene;
}

TreeNodeHeader* createDummyTree4()
{
    TreeNode* root = newNode(3, 2, 2, { 1.f, 1.f, 1.f }, { 1.f, 7.f, 1.f, 0.5f},
                             { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f });
    root->children[0] = newNode(3, 2, 4, { 1.f, 1.f, 1.f },{ 1.f, 1.f, 1.f, 0.5f},
                                { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f });
    root->children[1] = newNode(3, 5, 2, { 0.f, 0.f, 0.f },{ 1.f, 1.f, 1.f, 0.5f},
                                { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
    root->children[2] = newNode(7, 2, 2, { 0.f, 0.f, 0.f },{ 1.f, 3.f, 1.f, 0.5f},
                                { 0.f, 0.f, 0.f }, { 1.f, 1.f, 2.f });
    root->children[0]->children[0] = newNode(3, 9, 2, { 1.f, 1.f, 1.f },
                                             { 1.f, 1.f, 1.f, 0.5f},{ 1.f, 1.f, 1.f },
                                             { 4.f, 1.f, 1.f });
    root->children[0]->children[1] = newNode(3, 3, 2, { 0.f, 1.f, 0.f },
                                             { 1.f, 1.f, 3.f, 0.5f},{ 0.f, 0.f, 0.f }, { 1.f, 4.f, 1.f });
    root->children[2]->children[0] = newNode(10, 2, 2, { 0.f, 0.f, 0.f },
                                             { 2.f, 1.f, 1.f, 3.5f},{ 0.f, 0.f, 0.f }, { 7.f, 1.f, 1.f });
    root->children[2]->children[1] = newNode(3, 4, 2, { 0.f, 1.f, 0.f },
                                             { 1.f, 1.f, 1.f, 1.5f},{ 0.f, 0.f, 0.f }, { 1.f, 1.f, 3.f });
    root->children[2]->children[2] = newNode(7, 2, 2, { 0.f, 0.f, 0.f },
                                             { 1.f, 1.f, 7.f, 0.5f},{ 0.f, 0.f, 0.f }, { 4.f, 1.f, 1.f });
    root->children[2]->children[3] = newNode(1, 2, 7, { 1.f, 1.f, 1.f },
                                             { 1.f, 1.f, 1.f, 2.5f},{ 1.f, 1.f, 1.f }, { 1.f, 1.f, 3.f });
    root->children[0]->children[1]->children[0] = newNode(7,7,7, { 0.f, 0.f, 0.f },
                                                          { 1.f, 1.f, 1.f, 3.5f},{ 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f });

    TreeNodeHeader* scene = new TreeNodeHeader(root, 3, 1);
    return scene;
}


class SerilizerTests {

private:
    static void recursive_TreeTest(TreeNode& preticted_tree, TreeNode& tree) {
        assert(preticted_tree.data.rotation ==  tree.data.rotation);
        assert(preticted_tree.data.move ==  tree.data.move);
        assert(preticted_tree.data.scale ==  tree.data.scale);
        assert(preticted_tree.data.id_texture ==  tree.data.id_texture);
        assert(preticted_tree.data.id_name ==  tree.data.id_name);
        assert(preticted_tree.data.id_type ==  tree.data.id_type);
        for (int i = 0; preticted_tree.children[i] && tree.children[i]; ++i) {
            recursive_TreeTest(*preticted_tree.children[i], *tree.children[i]);
        }
    }
public:
    static void TreeTest1() {
        std::string str = "{\"id_frame\":3,\"root\":{\"children\":[{\"data\":{\"color\":[1.0,1.0,1.0,0.5],\"id_name\""
                          ":2,\"id_texture\":4,\"id_type\":3,\"move\":[1.0,1.0,1.0],\"rotation\":[0.0,0.0,0.0],\"scale\""
                          ":[1.0,1.0,1.0]}}],\"data\":{\"color\":[1.0,7.0,1.0,0.5],\"id_name\":2,\"id_texture\":2,\"id_type"
                          "\":3,\"move\":[1.0,1.0,1.0],\"rotation\":[0.0,0.0,0.0],\"scale\":[1.0,1.0,1.0]}},\"time\":4}";
        Serializer s;
        TreeNodeHeader* root = createDummyTree1();
        assert(str == s.serialize_to_string(*root));
        TreeNodeHeader* unserilized_root = s.unserialize_from_string(str);
        assert(unserilized_root->id_frame == root->id_frame);
        assert(unserilized_root->time == root->time);

        recursive_TreeTest(*unserilized_root->root, *root->root);

        std::cout<<"TEST1 PASSED"<<std::endl;
    }
    static void TreeTest2() {
        Serializer s;
        TreeNodeHeader* root = createDummyTree2();
        std::string str = s.serialize_to_string(*root);

        TreeNodeHeader* unserilized_root = s.unserialize_from_string(str);
        assert(unserilized_root->id_frame == root->id_frame);
        assert(unserilized_root->time == root->time);
        recursive_TreeTest(*unserilized_root->root, *root->root);
        std::cout<<"TEST2 PASSED"<<std::endl;
    }
    static void TreeTest3() {
        std::string str= "{\"id_frame\":8,\"root\":{\"children\":[{\"children\":[{\"data\":{\"color\":[1.0,1.0,1.0,0.5],"
                         "\"id_name\":9,\"id_texture\":2,\"id_type\":3,\"move\":[1.0,1.0,1.0],\"rotation\":[1.0,1.0,1.0],"
                         "\"scale\":[4.0,1.0,1.0]}},{\"data\":{\"color\":[1.0,1.0,3.0,0.5],\"id_name\":3,\"id_texture\":2,"
                         "\"id_type\":3,\"move\":[0.0,1.0,0.0],\"rotation\":[0.0,0.0,0.0],\"scale\":[1.0,4.0,1.0]}}],\"data"
                         "\":{\"color\":[1.0,1.0,1.0,0.5],\"id_name\":2,\"id_texture\":4,\"id_type\":3,\"move\":[1.0,1.0,1.0],"
                         "\"rotation\":[0.0,0.0,0.0],\"scale\":[1.0,1.0,1.0]}},{\"data\":{\"color\":[1.0,1.0,1.0,0.5],"
                         "\"id_name\":5,\"id_texture\":2,\"id_type\":3,\"move\":[0.0,0.0,0.0],\"rotation\":[1.0,1.0,1.0],"
                         "\"scale\":[1.0,1.0,1.0]}},{\"data\":{\"color\":[1.0,3.0,1.0,0.5],\"id_name\":2,\"id_texture\":2,"
                         "\"id_type\":7,\"move\":[0.0,0.0,0.0],\"rotation\":[0.0,0.0,0.0],\"scale\":[1.0,1.0,2.0]}}],"
                         "\"data\":{\"color\":[1.0,7.0,1.0,0.5],\"id_name\":2,\"id_texture\":2,\"id_type\":3,\"move"
                         "\":[1.0,1.0,1.0],\"rotation\":[0.0,0.0,0.0],\"scale\":[1.0,1.0,1.0]}},\"time\":4}";
        TreeNodeHeader* root = createDummyTree3();
        Serializer s;
        assert(str ==  s.serialize_to_string(*root));
        TreeNodeHeader* unserialized_root = s.unserialize_from_string(str);
        assert(unserialized_root->id_frame == root->id_frame);
        assert(unserialized_root->time == root->time);
        recursive_TreeTest(*unserialized_root->root, *root->root);
        std::cout<<"TEST3 PASSED"<<std::endl;
    }
    static void TreeTest4() {
        Serializer s;
        TreeNodeHeader* root = createDummyTree4();
        std::string str = s.serialize_to_string(*root);

        TreeNodeHeader* unserilized_root = s.unserialize_from_string(str);
        assert(unserilized_root->id_frame == root->id_frame);
        assert(unserilized_root->time == root->time);

        recursive_TreeTest(*unserilized_root->root, *root->root);
        std::cout<<"TEST4 PASSED"<<std::endl;
    }
};
