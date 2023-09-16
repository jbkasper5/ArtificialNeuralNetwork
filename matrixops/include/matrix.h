#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "macros.h"

typedef struct matrix_s{
    uint32_t rows;
    uint32_t cols;
    double* data;
} matrix_t;

// matrix initialization
matrix_t* zero_matrix(uint32_t rows, uint32_t cols);                                                    // check
matrix_t* one_matrix(uint32_t rows, uint32_t cols);                                                     // check
matrix_t* randi_matrix(uint32_t rows, uint32_t cols, int32_t lower_bound, int32_t upper_bound);         // check
matrix_t* randd_matrix(uint32_t rows, uint32_t cols, double lower_bound, double upper_bound);           // check
matrix_t* he_weight_matrix(uint32_t input_dim, uint32_t output_dim);
matrix_t* xavier_weight_matrix(uint32_t input_dim, uint32_t output_dim);
matrix_t* bias_matrix(uint32_t layer_dim);

// sample from a uniform distribution
double sample_normal(double mean, double standard_deviation);

// print a matrix
void show(matrix_t* mat);

// free memory allocated by a matrix
void matrix_destroy(matrix_t* mat);