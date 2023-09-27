#include <assert.h>
#include <string.h> // memcpy
#include "matrix.h"


matrix_t* matmul(matrix_t* mat1, matrix_t* mat2);
matrix_t* dimsum(matrix_t* m, uint32_t dim);

// element-wise multiplication between matrices
matrix_t* elwisemul(matrix_t* mat1, matrix_t* mat2, uint32_t in_place);
matrix_t* elwisesum(matrix_t* mat1, matrix_t* mat2, uint32_t in_place);
matrix_t* scalarmul(matrix_t* m, double s, uint32_t in_place);


// transpose a matrix
matrix_t* transpose(matrix_t* mat);

// apply activation functions element wise in the matrix
matrix_t* relu(matrix_t* m, uint32_t in_place);
matrix_t* relu_derivative(matrix_t* m, uint32_t in_place);
matrix_t* sigmoid(matrix_t* m, uint32_t in_place);
matrix_t* sigmoid_derivative(matrix_t* m, uint32_t in_place);

matrix_t* softmax(matrix_t* m, uint32_t dim, uint32_t in_place);
matrix_t* softmax_derivative(matrix_t* m, uint32_t dim);
matrix_t* softmax_jacobi_matrix(matrix_t* m, uint32_t dim);

