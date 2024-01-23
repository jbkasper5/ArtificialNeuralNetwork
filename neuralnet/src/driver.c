#include "net.h"
#include "config.h"

int main(int argc, char** argv){
    uint32_t model_inputs = (28 * 28);
    net_t* net = network_init(model_inputs);
    add_layer(net, 5, SIGMOID);
    add_layer(net, 8, RELU);
    network_destroy(net);

    dataloader_t* dataloader = create_mnist_dataloader(MNIST_TRAIN_PATH, MNIST_TEST_PATH);
    read_training_batch(dataloader, BATCH_SIZE);
    return 0;
}