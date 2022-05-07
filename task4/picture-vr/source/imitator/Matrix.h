#pragma once

#include <array>

using vec9 = std::array<float, 9>;

class Matrix {
public:
    static const int dim = 3;

    explicit Matrix(float elem);
    explicit Matrix(const vec9& matrix);

    Matrix& operator=(const Matrix& matrix);
    Matrix& operator*=(const Matrix& matrix);
    Matrix operator*(const Matrix& matrix) const;
    const float* operator[](int i) const;
private:
    float arr[dim][dim];
};
