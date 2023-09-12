#include "matrix_ops.h"

int main(int argc, char** argv){
    matrix* m1 = rand_matrix(2, 3);
    matrix* m2 = rand_matrix(3, 4);
    matrix* m3 = matmul(m1, m2);
    show(m1);
    show(m2);
    show(m3);
    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);
}