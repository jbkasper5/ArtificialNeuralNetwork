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

matrix_t* softmax(matrix_t* m, uint32_t in_place){
    matrix_t* ret_mat = (in_place) ? m : zero_matrix(m->rows, m->cols);
    uint32_t data_dim = m->rows;
    uint32_t batch_dim = m->cols;
    for(int i = 0; i < batch_dim; ++i){
        double sum = 0;
        for(int j = 0; j < data_dim; ++j) sum += exp(GET(m, i, j));
        for(int j = 0; j < data_dim; ++j){
            double new_value = exp(GET(m, i, j)) / sum;
            SET(ret_mat, i, j, new_value);
        }
    }
    return ret_mat;
}

matrix_t* softmax_jacobian(matrix_t* m){
    uint32_t data_dim = m->rows;
    uint32_t batch_dim = m->cols;
    matrix_t* jacobian = zero_matrix(data_dim, data_dim);
    double match, gradient, softmax_value;
    for(int i = 0; i < batch_dim; ++i){
        for(int j = 0; j < data_dim; ++j){
            softmax_value = GET(m, j, i);
            for(int k = 0; k < data_dim; ++k){
                gradient = softmax_value * ((j == k) - GET(m, k, i));
                SET(jacobian, j, k, gradient);
            }
        }
    }
    return jacobian;
}

matrix_t** batched_softmax_jacobian(matrix_t* m){
    uint32_t data_dim = m->rows;
    uint32_t batch_dim = m->cols;
    matrix_t** jacobian = (matrix_t**)malloc(sizeof(matrix_t*) * batch_dim);
    for(int i = 0; i < batch_dim; ++i) jacobian[i] = zero_matrix(data_dim, data_dim);
    double match, gradient, softmax_value;
    for(int i = 0; i < batch_dim; ++i){
        for(int j = 0; j < data_dim; ++j){
            softmax_value = GET(m, j, i);
            for(int k = 0; k < data_dim; ++k){
                gradient = softmax_value * ((j == k) - GET(m, k, i));
                SET(jacobian[i], j, k, gradient);
            }
        }
    }
    return jacobian;
}