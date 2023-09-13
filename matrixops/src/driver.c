#include "matrix_ops.h"

int main(int argc, char** argv){
    matrix_t* m1 = rand_matrix(1000, 1500);
    matrix_t* m2 = rand_matrix(1500, 2000);
    matrix_destroy(matmul(m1, m2));
    matrix_destroy(m1);
    matrix_destroy(m2);
}