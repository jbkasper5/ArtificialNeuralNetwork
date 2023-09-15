#include "matrix_ops.h"

// naive matrix multiplication
matrix_t* matmul(matrix_t* mat1, matrix_t* mat2){
    assert(mat1->cols == mat2->rows);
    matrix_t* ret_mat = zero_matrix(mat1->rows, mat2->cols);
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

// create 2 partitions per matrix, and perform 4 smaller sub-multiplications
// this function partitions m1 by dividing the columns by 2
matrix_t* matmul_optim1(matrix_t* mat1, matrix_t* mat2){
    assert(mat1->cols == mat2->rows);
    matrix_t* ret_mat = zero_matrix(mat1->rows, mat2->cols);
    uint32_t partition1_size = mat1->cols / 2;
    uint32_t partition2_size = mat2->cols - partition1_size;
    for(int m1row = 0; m1row < mat1->cols; ++m1row){

    }
    return ret_mat;
}

matrix_t* elwisemul(matrix_t* mat1, matrix_t* mat2){
    assert((mat1->rows == mat2->rows) && (mat1->cols == mat2->cols));
    matrix_t* ret_mat = zero_matrix(mat1->rows, mat1->cols);
    for(int i = 0; i < MATSIZE(mat1); ++i) ret_mat->data[i] = mat1->data[i] * mat2->data[i];
    return ret_mat;
}