#include <time.h>

#include "matrix_ops.h"

void test_forward_pass();

int main(int argc, char** argv){
    time_t start = clock();
    test_forward_pass();
    // test_backward_pass();
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

    matrix_t* bias1 = he_weight_matrix(1, 500);
    matrix_t* bias2 = he_weight_matrix(1, 100);
    matrix_t* bias3 = he_weight_matrix(1, 50);
    matrix_t* bias4 = he_weight_matrix(1, 10);

    P("Input: \t[%d, %d]\n", input->rows, input->cols);

    matrix_t* z1 = matmul(weight1, input);
    sum(z1, bias1, TRUE);
    matrix_t* activation_1 = sigmoid(z1, FALSE);
    P("A1: \t[%d, %d]\n", activation_1->rows, activation_1->cols);

    matrix_t* z2 = matmul(weight2, activation_1);
    sum(z2, bias2, TRUE);
    matrix_t* activation_2 = sigmoid(z2, FALSE);
    P("A2: \t[%d, %d]\n", activation_2->rows, activation_2->cols);

    matrix_t* z3 = matmul(weight3, activation_2);
    sum(z3, bias3, TRUE);
    matrix_t* activation_3 = sigmoid(z3, FALSE);
    P("A3: \t[%d, %d]\n", activation_3->rows, activation_3->cols);

    matrix_t* z4 = matmul(weight4, activation_3);
    sum(z4, bias4, TRUE);
    matrix_t* activation_4 = sigmoid(z4, FALSE);
    P("A4: \t[%d, %d]\n", activation_4->rows, activation_4->cols);
    
    show(activation_4);
}