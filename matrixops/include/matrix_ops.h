#include <assert.h>
#include <string.h> // memcpy
#include "matrix.h"

// naive approach
matrix_t* matmul(matrix_t* mat1, matrix_t* mat2);

// divide each matrix into 2 partitions
matrix_t* matmul_optim1(matrix_t* mat1, matrix_t* mat2);

// element-wise multiplication between matrices
matrix_t* elwisemul(matrix_t* mat1, matrix_t* mat2);

// transpose a matrix
matrix_t* transpose(matrix_t* mat);

// apply activation functions element wise in the matrix
matrix_t* relu(matrix_t* m);
matrix_t* sigmoid(matrix_t* m);

matrix_t* relu_derivative(matrix_t* m);
matrix_t* sigmoid_derivative(matrix_t* m);

matrix_t* softmax(matrix_t* m, uint32_t dim);
