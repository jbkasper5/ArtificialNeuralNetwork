#include <time.h>

#include "matrix_ops.h"

void test_forward_pass();

int main(int argc, char** argv){
    time_t start = clock();
    test_forward_pass();
    printf("Completed in: %f seconds.\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    return 0;
}

void test_forward_pass(){
    uint32_t batch_size = 5;

    // input has 784 features, and a batch size of batch_size
    matrix_t* input = randi_matrix(784, batch_size, 1, 10);

    // define the weight matrix with (in_features, out_features)
    matrix_t* weight1 = he_weight_matrix(784, 500);
    matrix_t* weight2 = he_weight_matrix(500, 100);
    matrix_t* weight3 = he_weight_matrix(100, 50);
    matrix_t* weight4 = he_weight_matrix(50, 10);
    P("Input: \t[%d, %d]\n", input->rows, input->cols);
    matrix_t* activation_1 = matmul(weight1, input);
    P("A1: \t[%d, %d]\n", activation_1->rows, activation_1->cols);
    matrix_t* activation_2 = matmul(weight2, activation_1);
    P("A2: \t[%d, %d]\n", activation_2->rows, activation_2->cols);
    matrix_t* activation_3 = matmul(weight3, activation_2);
    P("A3: \t[%d, %d]\n", activation_3->rows, activation_3->cols);
    matrix_t* activation_4 = matmul(weight4, activation_3);
    P("A4: \t[%d, %d]\n", activation_4->rows, activation_4->cols);
    show(activation_4);
}