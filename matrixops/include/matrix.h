#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "macros.h"

typedef struct matrix_s{
    uint32_t rows;
    uint32_t cols;
    double* data;
} matrix_t;

// matrix initialization
matrix_t* umatrix(uint32_t rows, uint32_t cols);
matrix_t* zero_matrix(uint32_t rows, uint32_t cols);
matrix_t* one_matrix(uint32_t rows, uint32_t cols);
matrix_t* rand_matrix(uint32_t rows, uint32_t cols);

// print a matrix
void show(matrix_t* mat);

// free memory allocated by a matrix
void matrix_destroy(matrix_t* mat);