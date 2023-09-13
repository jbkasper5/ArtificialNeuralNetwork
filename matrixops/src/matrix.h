#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef DDEBUG
#define p(...) (printf(__VA_ARGS__))
#else 
#define p(...)
#endif

#define MATSIZE(m) (m->rows * m->cols)
#define get(mat, i, j) (mat->data[i * mat->cols + j])

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