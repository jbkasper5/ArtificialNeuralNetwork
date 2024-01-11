#include "dataloader.h"

dataloader_t* create_mnist_dataloader(char* trainpath, char* testpath){
    dataloader_t* dataloader = malloc(sizeof(dataloader_t));
    dataloader->trainloader = assemble_train_paths(trainpath);
    dataloader->testloader = assemble_test_paths(testpath);
    return dataloader;
}

splitloader_t* assemble_train_paths(char* trainpath){
    splitloader_t* trainloader = malloc(sizeof(splitloader_t));
    trainloader->length = NUM_TRAINING_FILES;
    trainloader->samples = malloc(sizeof(sampletuple_t) * trainloader->length);

    DIR* train;
    DIR* class_dir;
    struct dirent* train_folders;
    struct dirent* class_files;
    char currpath[100];
    char filepath[MAX_FILENAME_LENGTH];
    train = opendir(trainpath);

    int filecount = 0;
    if(train){
        while((train_folders = readdir(train)) != NULL){
            if(train_folders->d_name[0] != '.'){
                strcpy(currpath, trainpath);
                strcat(currpath, "/");
                strcat(currpath, train_folders->d_name);
                class_dir = opendir(currpath);
                if(class_dir){
                    while((class_files = readdir(class_dir)) != NULL){
                        if(class_files->d_type == DT_REG){
                            strcpy(filepath, currpath);
                            strcat(filepath, "/");
                            strcat(filepath, class_files->d_name);
                            trainloader->samples[filecount].path = malloc(sizeof(char) * (MAX_FILENAME_LENGTH));
                            strcpy(trainloader->samples[filecount].path, filepath);
                            trainloader->samples[filecount++].label = atoi(train_folders->d_name);
                        }
                    }
                }
                closedir(class_dir);
            }
        }
    }
    closedir(train);
    return trainloader;
}

splitloader_t* assemble_test_paths(char* testpath){
    splitloader_t* testloader = malloc(sizeof(splitloader_t));
    testloader->length = NUM_TEST_FILES;
    testloader->samples = malloc(sizeof(sampletuple_t) * testloader->length);

    DIR* test;
    DIR* class_dir;
    struct dirent* test_folders;
    struct dirent* class_files;
    char currpath[100];
    char filepath[MAX_FILENAME_LENGTH];
    test = opendir(testpath);

    int filecount = 0;
    if(test){
        while((test_folders = readdir(test)) != NULL){
            if(test_folders->d_name[0] != '.'){
                strcpy(currpath, testpath);
                strcat(currpath, "/");
                strcat(currpath, test_folders->d_name);
                class_dir = opendir(currpath);
                if(class_dir){
                    while((class_files = readdir(class_dir)) != NULL){
                        if(class_files->d_type == DT_REG){
                            strcpy(filepath, currpath);
                            strcat(filepath, "/");
                            strcat(filepath, class_files->d_name);
                            testloader->samples[filecount].path = malloc(sizeof(char) * MAX_FILENAME_LENGTH);
                            strcpy(testloader->samples[filecount].path, filepath);
                            testloader->samples[filecount++].label = atoi(test_folders->d_name);
                        }
                    }
                }
                closedir(class_dir);
            }
        }
    }
    closedir(test);
    return testloader;
}

void dataloader_destroy(dataloader_t* dataloader){
    return;
}

modeltuple_t* read_training_sample(dataloader_t* dataloader, int index){
    modeltuple_t* tuple = malloc(sizeof(modeltuple_t));
    return NULL;
}

modeltuple_t* read_training_batch(dataloader_t* dataloader, int index, int batch_size){
    return NULL;
}

modeltuple_t* read_test_sample(dataloader_t* dataloader, int index){
    return NULL;
}

modeltuple_t* read_test_batch(dataloader_t* dataloader, int index, int batch_size){
    return NULL;
}