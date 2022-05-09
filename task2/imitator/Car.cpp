#include <cmath>
#include <iostream>

#include "Car.h"
#include "TreeNode.h"
#include "Matrix.h"

Car::Car(DataNode new_data) : TreeNode(new_data, wheels_count) {
    vec3 moves[] = {
            { -1.f,  1.f, 0.f },
            {  1.f,  1.f, 0.f },
            { -1.f, -1.f, 0.f },
            {  1.f, -1.f, 0.f }
    };

    for (int i = 0; i < wheels_count; ++i) {
        // id_type of wheel is 2
        // id_name of wheel[i] is i
        DataNode wheel_i_data(2, i, data.scale, data.rotation,
                              moves[i], data.id_texture, data.color);
        add(new TreeNode(wheel_i_data, 0));
    }
}

Car::~Car() {
    for (int i = 0; i < wheels_count; ++i) {
        delete children[i];
    }
}

//void Car::display(int obj_index, int iteration) const {
//    std::cout << "\n******************************\n";
//    const TreeNode* node = obj_index == 4 ? this : children[obj_index];
//    if (obj_index == 4) {
//        std::cout << "car info:\n";
//    }
//    else {
//        std::cout << "wheel " << obj_index << " info:\n";
//    }
//    vec3 scale = node->get_scale();
//    vec3 rotation = node->get_rotation();
//    vec3 move = node->get_move();
//    std::cout << "iteration " << iteration << std::endl;
//    std::cout << "scale: " << scale[0] << " " << scale[1] << " " << scale[2] << std::endl;
//    std::cout << "rotation: " << rotation[0] << " " << rotation[1] << " " << rotation[2] << std::endl;
//    std::cout << "move: " << move[0] << " " << move[1] << " " << move[2] << std::endl;
//    std::cout << "******************************\n";
//}
//
//void Car::display(int iteration) const {
//    std::cout << std::endl;
//    for (int i = 4; i >= 0; --i) {
//        display(i, iteration);
//    }
//    std::cout << std::endl;
//}

//void Car::routine() {
//    const float l = 1.f, m = 1.f, n = 0.f;
//    const float d = std::sqrt(m*m + n*n);
//    const vec3 direction = { l, m, n };
//
//    Matrix R_x_minus_psi(vec9({
//                                      1.f,    0.f,    0.f,
//                                      0.f,    n/d,    -m/d,
//                                      0.f,    m/d,    n/d
//                              }));
//
//    Matrix R_x_psi(vec9({
//                                1.f,    0.f,    0.f,
//                                0.f,    n/d,    -m/d,
//                                0.f,    -m/d,   n/d
//                        }));
//
//    Matrix R_y_theta(vec9({
//                                  d,      0.f,    -l,
//                                  0.f,    1.f,    0.f,
//                                  l,      0.f,    d
//                          }));
//
//    Matrix R_y_minus_theta(vec9({
//                                        d,      0.f,    l,
//                                        0.f,    1.f,    0.f,
//                                        -l,     0.f,    d
//                                }));
//
//    Matrix R_z_phi(vec9({
//                                .8f,    .6f,    0.f,
//                                -.6f,   .8f,    0.f,
//                                0.f,    0.f,    1.f
//                        }));
//
//    // rotation matrix around horizontal axis perpendicular to direction
//    Matrix M = R_z_phi * R_y_theta * R_x_psi;
//
//    for (int i = 0; i < 3; ++i) {
//        //display(i);
//        for (int j = 0; j < 3; ++j) {
//            data.move[j] += direction[j];
//        }
//        // rotate wheels
//        for (int j = 0; j < wheels_count; ++j) {
//            children[j]->set_rotation(rotation_from_matrix(matrix_from_rotation() * M));
//        }
//    }
//    //display(3);
//}
