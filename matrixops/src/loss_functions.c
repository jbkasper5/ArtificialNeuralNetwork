#include "matrixops.h"

matrix_t* mse(matrix_t* output, matrix_t* truth, uint32_t in_place){
    assert(output->rows == truth->rows && output->cols == truth->cols);
    matrix_t* ret_mat = (in_place) ? output : zero_matrix(output->rows, output->cols);
    for(int i = 0; i < MATSIZE(output); ++i) ret_mat->data[i] = pow(output->data[i] - truth->data[i], 2);
    return ret_mat;
}

matrix_t* mse_derivative(matrix_t* output, matrix_t* truth, uint32_t in_place){
    assert(output->rows == truth->rows && output->cols == truth->cols);
    matrix_t* ret_mat = (in_place) ? output : zero_matrix(output->rows, output->cols);
    for(int i = 0; i < MATSIZE(output); ++i) ret_mat->data[i] = 2 * (output->data[i] - truth->data[i]);
    return ret_mat;
}

matrix_t* binary_cross_entropy(matrix_t* output, matrix_t* truth, uint32_t in_place){
    assert(output->rows == truth->rows && output->cols == truth->cols);
    matrix_t* ret_mat = (in_place) ? output : zero_matrix(output->rows, output->cols);
    for(int i = 0; i < MATSIZE(output); ++i) ret_mat->data[i] = -(truth->data[i] * log(output->data[i])) - ((1 - truth->data[i]) * log(1 - output->data[i]));
    return ret_mat;
}

matrix_t* binary_cross_entropy_derivative(matrix_t* output, matrix_t* truth, uint32_t in_place){
    assert(output->rows == truth->rows && output->cols == truth->cols);
    matrix_t* ret_mat = (in_place) ? output : zero_matrix(output->rows, output->cols);
    for(int i = 0; i < MATSIZE(output); ++i) ret_mat->data[i] = (output->data[i] - truth->data[i]) / (output->data[i] * (1 - output->data[i]));
    return ret_mat;
}