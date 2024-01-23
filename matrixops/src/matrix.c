#include "matrix.h"

// initialize a matrix of size (rows, cols) with zeros
matrix_t* zero_matrix(uint32_t rows, uint32_t cols){
    matrix_t* mat = (matrix_t*)malloc(sizeof(matrix_t));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double*)calloc(MATSIZE(mat), sizeof(double));
    return mat;
}

// initialize a matrix of size (rows, cols) with ones
matrix_t* one_matrix(uint32_t rows, uint32_t cols){
    matrix_t* mat = (matrix_t*)malloc(sizeof(matrix_t));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double*)malloc(MATSIZE(mat) * sizeof(double));
    for(int i = 0; i < (rows * cols); ++i) mat->data[i] = 1;
    return mat;
}

// random integer matrix
matrix_t* randi_matrix(uint32_t rows, uint32_t cols, int32_t lower_bound, int32_t upper_bound){
    matrix_t* mat = (matrix_t*)malloc(sizeof(matrix_t));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double*)malloc(MATSIZE(mat) * sizeof(double));
    for(int i = 0; i < (MATSIZE(mat)); ++i) mat->data[i] = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;
    return mat;
}

// random double matrix
matrix_t* randd_matrix(uint32_t rows, uint32_t cols, double lower_bound, double upper_bound){
    return NULL;
}

// random normally distributed weight matrix (using he initialization)
matrix_t* he_weight_matrix(uint32_t input_dim, uint32_t output_dim){
    matrix_t* weight_matrix = (matrix_t*)malloc(sizeof(matrix_t));
    weight_matrix->rows = output_dim;
    weight_matrix->cols = input_dim;
    weight_matrix->data = (double*)malloc(MATSIZE(weight_matrix) * sizeof(double));
    for(int i = 0; i < MATSIZE(weight_matrix); ++i) weight_matrix->data[i] = sample_normal(0, sqrt(2 / (double)input_dim));
    return weight_matrix;
}

// random uniformally distributed weight matrix (using xavier initialization)
matrix_t* xavier_weight_matrix(uint32_t input_dim, uint32_t output_dim){
    return NULL;
}

// he bias matrix initialization
matrix_t* he_bias_matrix(uint32_t layer_dim){
    return he_weight_matrix(1, layer_dim);
}

// xavier bias matrix initialization
matrix_t* xavier_bias_matrix(uint32_t layer_dim){
    return xavier_weight_matrix(1, layer_dim);
}

// read a bmp image and return a 1D flattened matrix
matrix_t* read_bmp(char* path){
    bmpheader_t header;
    bmpinfoheader_t infoheader;
    P("Parsing image '%s'\n", path);

    // read necessary header information
    FILE* f = fopen(path, "r");
    fseek(f, 0, SEEK_SET);
    fread(&header, 1, sizeof(bmpheader_t), f);
    fread(&infoheader, 1, sizeof(bmpinfoheader_t), f);
    fseek(f, header.offset, SEEK_SET);
    matrix_t* mat = zero_matrix(infoheader.height * infoheader.width, 1);
    uint8_t px;
    for(int row = infoheader.height - 1; row >= 0; --row){
        for(int col = 0; col < infoheader.width; ++col){
            fread(&px, 1, sizeof(uint8_t), f);
            mat->data[(row * infoheader.height) + col] = px;
        }
    }
    return mat;
}

// read a batch of bmp images and assemble them into a 2d array
matrix_t* read_bmp_batch(char** paths, int batch_size){
    bmpheader_t header;
    bmpinfoheader_t infoheader;
    matrix_t* mat;
    uint8_t px;
    for(int sample_num = 0; sample_num < batch_size; ++sample_num){
        FILE* f = fopen(paths[sample_num], "r");
        fseek(f, 0, SEEK_SET);
        fread(&header, 1, sizeof(bmpheader_t), f);
        fread(&infoheader, 1, sizeof(bmpinfoheader_t), f);
        fseek(f, header.offset, SEEK_SET);
        if(!sample_num){
            mat = zero_matrix(infoheader.width * infoheader.height, batch_size);
        }
        for(int row = infoheader.height - 1; row >= 0; --row){
            for(int col = 0; col < infoheader.width; ++col){
                fread(&px, 1, sizeof(uint8_t), f);
                mat->data[(((row * infoheader.height) + col) * batch_size) + sample_num] = px;
            }
        }
    }
    return mat;
}

// one-hot matrix initialization for creating label matrices
matrix_t* onehot(int index, int classes){
    matrix_t* matrix = zero_matrix(classes, 1);
    matrix->data[index] = 1;
    return matrix;
}

matrix_t* onehot_batch(int* index, int classes, int batch_size){
    matrix_t* matrix = zero_matrix(classes, batch_size);
    for(int i = 0; i < batch_size; ++i){
        SET(matrix, *index++, i, 1);
    }
    return matrix;
}

// display a matrix
void show(matrix_t* mat){
    printf("\nMatrix (rows = %d, cols = %d): \n", mat->rows, mat->cols);
    for(int i = 0; i < (MATSIZE(mat)); ++i){
        if(i % mat->cols == 0){
            printf("\n\t");
        }
        // printf("%f ", mat->data[i]);
        printf("%d ", mat->data[i] ? 1 : 0);
    }
    printf("\n\n");
}

// free memory allocated by a matrix
void matrix_destroy(matrix_t* mat){
    // free data occupied by matrix
    free(mat->data);

    // free the matrix struct
    free(mat);
}

// sampling from a given uniform distribution using the box-muller method
double sample_normal(double mean, double standard_deviation){
    static double cached_random_value = 0;
    double res;
    if(!cached_random_value){
        double u1, u2, radius;
        do{
            u1 = 2 * rand() / ((double)RAND_MAX - 1);
            u2 = 2 * rand() / ((double)RAND_MAX - 1);
            radius = pow(u1, 2) + pow(u2, 2);
        }while(radius == 0 || radius >= 1);
        double temp = sqrt(-2.0 * log(radius) / radius);
        res = u1 * temp;
        double res2 = u2 * temp;
        cached_random_value = res2;
    }else{
        res = cached_random_value;
        cached_random_value = 0;
    }

    // apply shifts to the standard uniform distribution
    return (res * standard_deviation) + mean;
}