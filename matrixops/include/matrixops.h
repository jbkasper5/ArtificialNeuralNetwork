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
matrix_t* softmax(matrix_t* m, uint32_t in_place);
matrix_t* softmax_jacobian(matrix_t* m);
matrix_t** batched_softmax_jacobian(matrix_t* m);

// apply a given loss function
matrix_t* mse(matrix_t* output, matrix_t* truth, uint32_t in_place);
matrix_t* mse_derivative(matrix_t* output, matrix_t* truth, uint32_t in_place);
matrix_t* binary_cross_entropy(matrix_t* output, matrix_t* truth, uint32_t in_place);
matrix_t* binary_cross_entropy_derivative(matrix_t* output, matrix_t* truth, uint32_t in_place);

