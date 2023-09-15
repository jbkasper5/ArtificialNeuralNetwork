#include "matrix_ops.h"

void test_cache_metrics();

int main(int argc, char** argv){
    P("Hello!\n");
    return 0;
}

void test_cache_metrics(){
    matrix_t* m1 = rand_matrix(1000, 1500);
    matrix_t* m2 = rand_matrix(1500, 2000);
    matrix_destroy(matmul(m1, m2));
    matrix_destroy(m1);
    matrix_destroy(m2);
}