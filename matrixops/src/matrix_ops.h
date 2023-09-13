#include <assert.h>
#include "matrix.h"

matrix_t* matmul(matrix_t* mat1, matrix_t* mat2);
matrix_t* matmul3d(matrix_t* mat1, matrix_t* mat2);
matrix_t* elwisemul(matrix_t* mat1, matrix_t* mat2);
matrix_t* transpose(matrix_t* mat);

matrix_t* relu(matrix_t* mat1);
matrix_t* sigmoid(matrix_t* mat1);
