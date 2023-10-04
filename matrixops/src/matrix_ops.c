#include "matrixops.h"

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

matrix_t* dimsum(matrix_t* m, uint32_t dim){
    // dim = 0 -> row sum
    // dim = 1 -> column sum
    matrix_t* ret_mat = (dim) ? zero_matrix(1, m->cols) : zero_matrix(m->rows, 1);
    if(dim == 0){
        for(int i = 0; i < m->rows; ++i){
            for(int j = 0; j < m->cols; ++j){
                ret_mat->data[i] += GET(m, i, j);
            }
        }
    }else if(dim == 1){
        for(int i = 0; i < m->cols; ++i){
            for(int j = 0; j < m->rows; ++j){
                ret_mat->data[i] += GET(m, i, j);
            }
        }
    }else{
        printf("NOT IMPLEMENTED.");
    }
    return ret_mat;
}

matrix_t* transpose(matrix_t* m){
    matrix_t* mat_transpose = zero_matrix(m->cols, m->rows);
    for(int i = 0; i < mat_transpose->rows; ++i){
        for(int j = 0; j < mat_transpose->cols; ++j){
            mat_transpose->data[i * mat_transpose->cols + j] = GET(m, j, i);
        }
    }
    return mat_transpose;
}

matrix_t* elwisesum(matrix_t* mat1, matrix_t* mat2, uint32_t in_place){
    assert(mat1->rows == mat2->rows);
    matrix_t* ret_mat = (in_place) ? mat1 : zero_matrix(mat1->rows, mat2->cols);
    if(ret_mat->cols == mat2->cols){
        for(int i = 0; i < MATSIZE(ret_mat); ++i) ret_mat->data[i] += mat2->data[i];
    }else if(mat2->cols == 1){
        for(int i = 0; i < ret_mat->rows; ++i){
            for(int j = 0; j < ret_mat->cols; ++j){
                ret_mat->data[i * ret_mat->cols + j] += mat2->data[i];
            }
        }
    }else{
        printf("ADD ERR: Matrix [%d, %d] cannot be added with matrix [%d, %d].\n", mat1->rows, mat1->cols, mat2->rows, mat2->cols);
        exit(1);
    }
    return ret_mat;
}

matrix_t* scalarmul(matrix_t* m, double s, uint32_t in_place){
    matrix_t* ret_mat = (in_place) ? m : zero_matrix(m->rows, m->cols);
    for(int i = 0; i < MATSIZE(ret_mat); ++i) ret_mat->data[i] = m->data[i] * s;
    return ret_mat;
}

matrix_t* elwisemul(matrix_t* mat1, matrix_t* mat2, uint32_t in_place){
    assert((mat1->rows == mat2->rows) && (mat1->cols == mat2->cols));
    matrix_t* ret_mat = (in_place) ? mat1 : zero_matrix(mat1->rows, mat2->cols);
    if(ret_mat->cols == mat2->cols){
        for(int i = 0; i < MATSIZE(ret_mat); ++i) ret_mat->data[i] = mat1->data[i] * mat2->data[i];
    }else if(mat2->cols == 1){
        for(int i = 0; i < ret_mat->rows; ++i){
            for(int j = 0; j < ret_mat->cols; ++j){
                ret_mat->data[i * ret_mat->cols + j] = mat1->data[i] * mat2->data[i];
            }
        }
    }else{
        exit(1);
    }
    return ret_mat;
}