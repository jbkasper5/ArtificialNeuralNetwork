#include "dataloader.h"

dataloader_t* create_mnist_dataloader(char* trainpath, char* testpath){
    dataloader_t* dataloader = malloc(sizeof(dataloader_t));
    dataloader->trainloader = assemble_paths(trainpath);
    dataloader->testloader = assemble_paths(testpath);
    return dataloader;
}

splitloader_t* assemble_paths(char* path){
    splitloader_t* splitloader = malloc(sizeof(splitloader_t));
    splitloader->length = NUM_TRAINING_FILES;
    splitloader->samples = malloc(sizeof(sampletuple_t) * splitloader->length);

    DIR* split;
    DIR* class_dir;
    struct dirent* folders;
    struct dirent* class_files;
    char currpath[100];
    char filepath[MAX_FILENAME_LENGTH];
    split = opendir(path);

    int filecount = 0;
    if(split){
        while((folders = readdir(split)) != NULL){
            if(folders->d_name[0] != '.'){
                strcpy(currpath, path);
                strcat(currpath, "/");
                strcat(currpath, folders->d_name);
                class_dir = opendir(currpath);
                if(class_dir){
                    while((class_files = readdir(class_dir)) != NULL){
                        if(class_files->d_type == DT_REG){
                            strcpy(filepath, currpath);
                            strcat(filepath, "/");
                            strcat(filepath, class_files->d_name);
                            splitloader->samples[filecount].path = malloc(sizeof(char) * (MAX_FILENAME_LENGTH));
                            strcpy(splitloader->samples[filecount].path, filepath);
                            splitloader->samples[filecount++].label = atoi(folders->d_name);
                        }
                    }
                }
                closedir(class_dir);
            }
        }
    }
    closedir(split);
    splitloader->iterator = 0;
    return splitloader;
}

void dataloader_destroy(dataloader_t* dataloader){
    for(int i = 0; i < dataloader->trainloader->length; i++){
        free(dataloader->trainloader->samples[i].path);
    }

    for(int i = 0; i < dataloader->testloader->length; i++){
        free(dataloader->testloader->samples[i].path);
    }
    free(dataloader->trainloader);
    free(dataloader->testloader);
    free(dataloader);
}

modeltuple_t* read_training_sample(dataloader_t* dataloader){
    // TODO: ensure the iterator isn't at the end of the dataloader
    modeltuple_t* tuple = malloc(sizeof(modeltuple_t));
    sampletuple_t* sample = &dataloader->trainloader->samples[dataloader->trainloader->iterator++];
    tuple->input = read_bmp(sample->path);
    tuple->label = onehot(sample->label, N_CLASSES);
    DIM(tuple->input);
    DIM(tuple->label);
    return tuple;
}

modeltuple_t* read_training_batch(dataloader_t* dataloader, int batch_size){
    // TODO: ensure the iterator isn't at the end of the dataloader
    modeltuple_t* tuple = malloc(sizeof(modeltuple_t));
    sampletuple_t* sample;
    char** paths = malloc(sizeof(char*) * batch_size);
    int* labels = malloc(sizeof(int) * batch_size);
    for(int i = 0; i < batch_size; ++i){
        sample = &dataloader->trainloader->samples[dataloader->trainloader->iterator++];
        paths[i] = sample->path;
        labels[i] = sample->label;
    }
    tuple->input = read_bmp_batch(paths, batch_size);
    tuple->label = onehot_batch(labels, N_CLASSES, batch_size);
    DIM(tuple->input);
    DIM(tuple->label);
    free(paths);
    free(labels);
    return tuple;
}

modeltuple_t* read_test_sample(dataloader_t* dataloader){
    return NULL;
}

modeltuple_t* read_test_batch(dataloader_t* dataloader, int batch_size){
    return NULL;
}