#include "matrix.h"

// initialize a matrix of size (rows, cols) with zeros
matrix_t* zero_matrix(uint32_t rows, uint32_t cols){
    matrix_t* mat = (matrix_t*)malloc(sizeof(matrix_t));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double*)calloc(MATSIZE(mat), sizeof(double));
    return mat;
}

// initialize a matrix of size (rows, cols) with ones
matrix_t* one_matrix(uint32_t rows, uint32_t cols){
    matrix_t* mat = (matrix_t*)malloc(sizeof(matrix_t));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double*)malloc(MATSIZE(mat) * sizeof(double));
    for(int i = 0; i < (rows * cols); ++i) mat->data[i] = 1;
    return mat;
}

// initialize a matrix of size (rows, cols) with random values
matrix_t* rand_matrix(uint32_t rows, uint32_t cols){
    matrix_t* mat = (matrix_t*)malloc(sizeof(matrix_t));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double*)malloc(rows * cols * sizeof(double));
    int lower = 1;
    int upper = 10;
    for(int i = 0; i < (MATSIZE(mat)); ++i) mat->data[i] = (rand() % (upper - lower + 1)) + lower;
    return mat;
}

// display a matrix
void show(matrix_t* mat){
    printf("\nMatrix (rows = %d, cols = %d): \n", mat->rows, mat->cols);
    for(int i = 0; i < (MATSIZE(mat)); ++i){
        if(i % mat->cols == 0){
            printf("\n\t");
        }
        printf("%f ", mat->data[i]);
    }
    printf("\n\n");
}

void matrix_destroy(matrix_t* mat){
    // free data occupied by matrix
    free(mat->data);

    // free the matrix struct
    free(mat);
}