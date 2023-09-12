#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef DDEBUG
#define p(...) (printf(__VA_ARGS__))
#else 
#define p(...)
#endif

typedef struct matrix_s{
    uint32_t rows;
    uint32_t cols;
    double* data;
} matrix;

// matrix initialization
matrix* umatrix(uint32_t rows, uint32_t cols);
matrix* zero_matrix(uint32_t rows, uint32_t cols);
matrix* one_matrix(uint32_t rows, uint32_t cols);
matrix* rand_matrix(uint32_t rows, uint32_t cols);

// print a matrix
void show(matrix* mat);

// free memory allocated by a matrix
void matrix_destroy(matrix* mat);