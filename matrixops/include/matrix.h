#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h> // memcpy
#include "macros.h"

// for parsing bmp files into a matrix
#define BMP_WIDTH_LOCATION 18
#define BMP_HEIGHT_LOCATION 22
#define BMP_PIXEL_START 58

typedef struct matrix_s matrix_t;

typedef struct bmpheader_s bmpheader_t;
typedef struct bmpinfoheader_s bmpinfoheader_t;
typedef struct pixel_s pixel_t;

struct matrix_s{
    uint32_t rows;
    uint32_t cols;
    double* data;
};

#pragma pack(push,1)
struct bmpheader_s{
    uint8_t sig[2];
    uint32_t filesize;
    uint32_t reserved;
    uint32_t offset;
};

struct bmpinfoheader_s{
    uint32_t hsize;
    uint32_t width;
    uint32_t height;
    uint16_t colorplanes;
    uint16_t bitsperpixel;
    uint32_t compression;
    uint32_t size;
    uint32_t hres;
    uint32_t vres;
    uint32_t numcolors;
    uint32_t importantcolors;
};
#pragma pack(pop)


struct pixel_s{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// matrix initialization
matrix_t* zero_matrix(uint32_t rows, uint32_t cols);                                                    // check
matrix_t* one_matrix(uint32_t rows, uint32_t cols);                                                     // check
matrix_t* randi_matrix(uint32_t rows, uint32_t cols, int32_t lower_bound, int32_t upper_bound);         // check
matrix_t* randd_matrix(uint32_t rows, uint32_t cols, double lower_bound, double upper_bound);           // check
matrix_t* he_weight_matrix(uint32_t input_dim, uint32_t output_dim);
matrix_t* xavier_weight_matrix(uint32_t input_dim, uint32_t output_dim);
matrix_t* he_bias_matrix(uint32_t layer_dim);
matrix_t* xavier_bias_matrix(uint32_t layer_dim);
matrix_t* read_bmp(char* path);
matrix_t* read_bmp_batch(char** paths, int batch_size);
matrix_t* onehot(int index, int classes);
matrix_t* onehot_batch(int* index, int classes, int batch_size);

// sample from a uniform distribution
double sample_normal(double mean, double standard_deviation);

// print a matrix
void show(matrix_t* mat);

// free memory allocated by a matrix
void matrix_destroy(matrix_t* mat);