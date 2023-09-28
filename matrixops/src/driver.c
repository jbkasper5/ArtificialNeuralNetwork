#include <time.h>

#include "matrixops.h"

void test_pass_1();
void test_pass_2();

int main(int argc, char** argv){
    srand(time(NULL));
    time_t start = clock();
    // test_pass_1();
    // test_pass_2();
    matrix_t* test = zero_matrix(3, 1);
    for(int i = 0; i < MATSIZE(test); ++i) test->data[i] = i + 1;

    show(test);
    matrix_t* sm = softmax(test, FALSE);
    show(sm);
    matrix_t** jacobain = batched_softmax_jacobian(sm);
    show(jacobain[0]);
    matrix_destroy(test);
    matrix_destroy(sm);

    printf("Completed in: %f seconds.\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    return 0;
}

void test_pass_1(){
    uint32_t batch_size = 2;
    double learning_rate = 0.01;

    // input has 784 features, and a batch size of batch_size
    matrix_t* input = randi_matrix(784, batch_size, 1, 10);

    // define the weight matrix with (in_features, out_features)
    matrix_t* weight1 = he_weight_matrix(784, 500);
    matrix_t* weight2 = he_weight_matrix(500, 100);
    matrix_t* weight3 = he_weight_matrix(100, 10);
    matrix_t* weight4 = he_weight_matrix(10, 2);

    matrix_t* bias1 = he_bias_matrix(500);
    matrix_t* bias2 = he_bias_matrix(100);
    matrix_t* bias3 = he_bias_matrix(10);
    matrix_t* bias4 = he_bias_matrix(2);


    P("Input: \t[%d, %d]\n", input->rows, input->cols);

    matrix_t* z1 = matmul(weight1, input);
    elwisesum(z1, bias1, TRUE);
    matrix_t* activation_1 = sigmoid(z1, FALSE);
    P("A1: \t[%d, %d]\n", activation_1->rows, activation_1->cols);

    matrix_t* z2 = matmul(weight2, activation_1);
    elwisesum(z2, bias2, TRUE);
    matrix_t* activation_2 = sigmoid(z2, FALSE);
    P("A2: \t[%d, %d]\n", activation_2->rows, activation_2->cols);

    matrix_t* z3 = matmul(weight3, activation_2);
    elwisesum(z3, bias3, TRUE);
    matrix_t* activation_3 = sigmoid(z3, FALSE);
    P("A3: \t[%d, %d]\n", activation_3->rows, activation_3->cols);

    matrix_t* z4 = matmul(weight4, activation_3);
    elwisesum(z4, bias4, TRUE);
    matrix_t* activation_4 = softmax(z4, FALSE);
    P("A4: \t[%d, %d]\n", activation_4->rows, activation_4->cols);
    
    show(activation_4);

    matrix_t* db4 = he_weight_matrix(batch_size, 2);
    matrix_t* dw4 = matmul(db4, transpose(activation_3));

    matrix_t* db3 = elwisemul(sigmoid_derivative(z3, FALSE), matmul(transpose(weight4), db4), FALSE);
    matrix_t* dw3 = matmul(db3, transpose(activation_2));

    matrix_t* db2 = elwisemul(sigmoid_derivative(z2, FALSE), matmul(transpose(weight3), db3), FALSE);
    matrix_t* dw2 = matmul(db2, transpose(activation_1));

    matrix_t* db1 = elwisemul(sigmoid_derivative(z1, FALSE), matmul(transpose(weight2), db2), FALSE);
    matrix_t* dw1 = matmul(db1, transpose(input));

    scalarmul(dw1, learning_rate, TRUE);
    elwisesum(weight1, dw1, TRUE);

    scalarmul(dw2, learning_rate, TRUE);
    elwisesum(weight2, dw2, TRUE);

    scalarmul(dw3, learning_rate, TRUE);
    elwisesum(weight3, dw3, TRUE);

    scalarmul(dw4, learning_rate, TRUE);
    elwisesum(weight4, dw4, TRUE);

    matrix_t* get_sum = dimsum(db1, 0);
    scalarmul(get_sum, learning_rate, TRUE);
    elwisesum(bias1, get_sum, TRUE);

    get_sum = dimsum(db2, 0);
    scalarmul(get_sum, learning_rate, TRUE);
    elwisesum(bias2, get_sum, TRUE);

    get_sum = dimsum(db3, 0);
    scalarmul(get_sum, learning_rate, TRUE);
    elwisesum(bias3, get_sum, TRUE);

    get_sum = dimsum(db4, 0);
    scalarmul(get_sum, learning_rate, TRUE);
    elwisesum(bias4, get_sum, TRUE);
}

void test_pass_2(){
    int len = 9;
    int dims[] = {800, 400, 200, 100, 50, 25, 12, 6, 2};
    int batch_size = 5;
    double learning_rate = 0.05;

    matrix_t** weights = (matrix_t**)malloc(sizeof(matrix_t*) * (len - 1));
    matrix_t** dw = (matrix_t**)malloc(sizeof(matrix_t*) * (len - 1));
    matrix_t** biases = (matrix_t**)malloc(sizeof(matrix_t*) * (len - 1));
    matrix_t** db = (matrix_t**)malloc(sizeof(matrix_t*) * (len - 1));
    matrix_t** sums = (matrix_t**)malloc(sizeof(matrix_t*) * (len - 1));
    matrix_t** activations = (matrix_t**)malloc(sizeof(matrix_t*) * len);

    for(int i = 0; i < (len - 1); ++i) weights[i] = he_weight_matrix(dims[i], dims[i + 1]);
    for(int i = 0; i < (len - 1); ++i) biases[i] = he_bias_matrix(dims[i + 1]);

    activations[0] = randi_matrix(dims[0], batch_size, 0, 10);

    // compute forward pass
    for(int i = 1; i < len; ++i){
        P("Forward layer %d\n", i);
        sums[i - 1] = elwisesum(matmul(weights[i - 1], activations[i - 1]), biases[i - 1], TRUE);
        activations[i] = sigmoid(sums[i - 1], FALSE);
    }

    // compute backward pass
    db[len - 2] = he_weight_matrix(batch_size, dims[len - 1]);
    for(int i = len - 2; i > 0; --i){
        P("Backprop layer %d\n", i);
        matrix_t* a_transpose = transpose(activations[i]);
        dw[i] = matmul(db[i], a_transpose);

        matrix_t* w_transpose = transpose(dw[i]);
        matrix_t* f_prime = sigmoid_derivative(sums[i - 1], FALSE);

        db[i - 1] = elwisemul(matmul(w_transpose, db[i]), f_prime, TRUE);

        matrix_destroy(f_prime);
        matrix_destroy(a_transpose);
        matrix_destroy(w_transpose);
    }
    matrix_t* a0_transpose = transpose(activations[0]);
    dw[0] = matmul(db[0], a0_transpose);
    matrix_destroy(a0_transpose);

    // update gradients
    for(int i = 0; i < (len - 1); ++i){   
        P("Update to weight and bias %d\n", i);     
        scalarmul(dw[i], learning_rate, TRUE);
        elwisesum(weights[i], dw[i], TRUE);

        matrix_t* dbsum = dimsum(db[i], 0);
        scalarmul(dbsum, learning_rate, TRUE);
        elwisesum(biases[i], dbsum, TRUE);
        matrix_destroy(dbsum);
    }
}