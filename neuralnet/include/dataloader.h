#include "matrixops.h"
#include "config.h"
#include <dirent.h>
#include <stdio.h>

typedef struct dataloader_s dataloader_t;
typedef struct splitloader_s splitloader_t;
typedef struct sampletuple_s sampletuple_t;
typedef struct modeltuple_s modeltuple_t;

struct dataloader_s{
    splitloader_t* trainloader;
    splitloader_t* testloader;
};

struct splitloader_s{
    sampletuple_t* samples;
    uint64_t length;
};

struct sampletuple_s{
    char* path;
    int8_t label;
};

struct modeltuple_s{
    matrix_t* input;
    matrix_t* label;
};

dataloader_t* create_mnist_dataloader(char* trainpath, char* testpath);
splitloader_t* assemble_train_paths(char* trainpath);
splitloader_t* assemble_test_paths(char* testpath);
void dataloader_destroy(dataloader_t* dataloader);

modeltuple_t* read_training_sample(dataloader_t* dataloader, int index);
modeltuple_t* read_training_batch(dataloader_t* dataloader, int index, int batch_size);
modeltuple_t* read_test_sample(dataloader_t* dataloader, int index);
modeltuple_t* read_test_batch(dataloader_t* dataloader, int index, int batch_size);