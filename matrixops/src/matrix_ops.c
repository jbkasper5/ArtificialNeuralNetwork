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

matrix_t* transpose(matrix_t* m){
    // switch every (i, j) for (j, i)
    matrix_t* mat_transpose = zero_matrix(m->cols, m->rows);
    for(int i = 0; i < mat_transpose->rows; ++i){
        for(int j = 0; j < mat_transpose->cols; ++j){
            mat_transpose->data[i * mat_transpose->cols + j] = GET(m, j, i);
        }
    }
    return mat_transpose;
}

matrix_t* sum(matrix_t* mat1, matrix_t* mat2, int in_place){
    P("Mat1: [%d, %d]\n", mat1->rows, mat1->cols);
    P("Mat2: [%d, %d]\n", mat2->rows, mat2->cols);
    assert(mat1->rows == mat2->rows);
    matrix_t* ret_mat = (in_place) ? zero_matrix(mat1->rows, mat2->cols) : mat1;
    if(ret_mat->cols == mat2->cols){
        for(int i = 0; i < MATSIZE(ret_mat); ++i) ret_mat->data[i] += mat2->data[i];
    }else if(mat2->cols == 1){
        for(int i = 0; i < ret_mat->rows; ++i){
            for(int j = 0; j < ret_mat->cols; ++j){
                ret_mat->data[i * ret_mat->cols + j] += mat2->data[i];
            }
        }
    }else{
        exit(1);
    }
    return ret_mat;
}

matrix_t* relu(matrix_t* m, int in_place){
    matrix_t* ret_mat = (in_place) ? zero_matrix(m->rows, m->cols) : m;
    for(int i = 0; i < MATSIZE(ret_mat); ++i) ret_mat->data[i] = MAX(m->data[i], 0);
    return ret_mat;
}

matrix_t* sigmoid(matrix_t* m, int in_place){
    matrix_t* ret_mat = (in_place) ? zero_matrix(m->rows, m->cols) : m;
    for(int i = 0; i < MATSIZE(m); ++i) ret_mat->data[i] = (1 / (double)(1 + exp(-m->data[i])));
    return ret_mat;
}

matrix_t* relu_derivative(matrix_t* m){
    return NULL;
}

matrix_t* sigmoid_derivative(matrix_t* m){
    return NULL;
}


matrix_t* elwisemul(matrix_t* mat1, matrix_t* mat2){
    assert((mat1->rows == mat2->rows) && (mat1->cols == mat2->cols));
    matrix_t* ret_mat = zero_matrix(mat1->rows, mat1->cols);
    for(int i = 0; i < MATSIZE(mat1); ++i) ret_mat->data[i] = mat1->data[i] * mat2->data[i];
    return ret_mat;
}