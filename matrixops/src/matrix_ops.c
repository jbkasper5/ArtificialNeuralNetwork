#include "matrix_ops.h"

matrix* matmul(matrix* mat1, matrix* mat2){
    assert(mat1->cols == mat2->rows);
    matrix* ret_mat = zero_matrix(mat1->rows, mat2->cols);
    // for each row vector of m1
    for(int m1row = 0; m1row < mat1->rows; ++m1row){
        // for each column vector of m2
        for(int m2col = 0; m2col < mat2->cols; ++m2col){
            // compute the dot product of row vector and column vector
            for(int i = 0; i < mat1->cols; ++i){
                ret_mat->data[(m1row * mat2->cols) + m2col] += (mat1->data[(m1row * mat1->cols) + i] * mat2->data[m2col + (i * mat2->cols)]);
            }
        }
    }
    return ret_mat;
}

matrix* elwisemul(matrix* mat1, matrix* mat2){
    assert((mat1->rows == mat2->rows) && (mat1->cols == mat2->cols));
    matrix* ret_mat = zero_matrix(mat1->rows, mat1->cols);
    for(int i = 0; i < (mat1->rows * mat1->cols); ++i) ret_mat->data[i] = mat1->data[i] * mat2->data[i];
    return ret_mat;
}