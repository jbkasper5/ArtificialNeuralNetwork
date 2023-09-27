#include "matrixops.h"

double sigmoid_function(double val);


matrix_t* relu(matrix_t* m, uint32_t in_place){
    matrix_t* ret_mat = (in_place) ? m : zero_matrix(m->rows, m->cols);
    for(int i = 0; i < MATSIZE(ret_mat); ++i) ret_mat->data[i] = MAX(m->data[i], 0);
    return ret_mat;
}

matrix_t* relu_derivative(matrix_t* m, uint32_t in_place){
    matrix_t* ret_mat = (in_place) ? m : zero_matrix(m->rows, m->cols);
    for(int i = 0; i < MATSIZE(ret_mat); ++i) ret_mat->data[i] = MAX(m->data[i], 0) / m->data[i];
    return ret_mat;
}

double sigmoid_function(double val){
    return (1 / (double)(1 + exp(val)));
}

matrix_t* sigmoid(matrix_t* m, uint32_t in_place){
    matrix_t* ret_mat = (in_place) ? m : zero_matrix(m->rows, m->cols);
    for(int i = 0; i < MATSIZE(m); ++i) ret_mat->data[i] = sigmoid_function(m->data[i]);
    return ret_mat;
}

matrix_t* sigmoid_derivative(matrix_t* m, uint32_t in_place){
    matrix_t* ret_mat = (in_place) ? m : zero_matrix(m->rows, m->cols);
    for(int i = 0; i < MATSIZE(m); ++i) ret_mat->data[i] = sigmoid_function(m->data[i]) * sigmoid_function(m->data[i]);
    return ret_mat;
}

matrix_t* softmax(matrix_t* m, uint32_t dim, uint32_t in_place){
    matrix_t* ret_mat = (in_place) ? m : zero_matrix(m->rows, m->cols);
    uint32_t dimension = (dim) ? m->cols : m->rows;
    uint32_t antidimension = (dim) ? m->rows : m->cols;
    for(int i = 0; i < dimension; ++i){
        double sum = 0;
        for(int j = 0; j < antidimension; ++j) sum += exp((dim) ? GET(m, j, i) : GET(m, i, j));
        for(int j = 0; j < antidimension; ++j){
            double new_value = exp((dim) ? GET(m, j, i) : GET(m, i, j)) / sum;
            (dim) ? SET(ret_mat, j, i, new_value) : SET(ret_mat, i, j, new_value);
        }
    }
    return ret_mat;
}

matrix_t* softmax_derivative(matrix_t* m, uint32_t dim){
    return NULL;
}