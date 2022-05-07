#include "Matrix.h"

Matrix::Matrix(float elem) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            arr[i][j] = elem;
        }
    }
}

Matrix::Matrix(const vec9& matrix) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            arr[i][j] = matrix[i * dim + j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& matrix) {
    if (this == &matrix) {
        return *this;
    }
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            arr[i][j] = matrix.arr[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& matrix) {
    Matrix res(0.f);
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            for (int k = 0; k < dim; ++k) {
                res.arr[i][j] += arr[i][k] * matrix.arr[k][j];
            }

        }
    }
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            arr[i][j] = res.arr[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix& matrix) const {
    Matrix res = *this;
    return res *= matrix;
}

const float* Matrix::operator[](int i) const {
    return arr[i];
}

