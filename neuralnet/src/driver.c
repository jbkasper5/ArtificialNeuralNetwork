#include "net.h"
#include "config.h"
#include "pbar.h"


#define EPOCHS 75
#define BATCH_SIZE 16
#define LEARNING_RATE 0.001

void pbar();

int main(int argc, char** argv){
    uint32_t model_inputs = (28 * 28);
    net_t* net = network_init(model_inputs);
    add_layer(net, 5, SIGMOID);
    add_layer(net, 8, RELU);

    dataloader_t* dataloader = create_mnist_dataloader(MNIST_TRAIN_PATH, MNIST_TEST_PATH);
    config_t* config = config_init(EPOCHS, BATCH_SIZE, LEARNING_RATE);

    train(net, dataloader, config);
    test(net, dataloader, config);

    dataloader_destroy(dataloader);
    network_destroy(net);

    int len = 45;
    pbar_t* pbar = pbar_create(len);
    for(int i = 0; i < len; ++i){
        pbar_tick(pbar);
        usleep(500000);
    }
    pbar_destroy(pbar);

    len = 100;
    pbar = pbar_create(len);
    for(int i = 0; i < len; ++i){
        pbar_tick(pbar);
        usleep(100000);
    }
    pbar_destroy(pbar);

    len = 100;
    pbar = pbar_create(len);
    for(int i = 0; i < len; ++i){
        pbar_tick(pbar);
        usleep(100000);
    }
    pbar_destroy(pbar);
    return 0;
}