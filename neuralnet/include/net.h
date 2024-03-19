#include "dataloader.h"

enum activation_functions{NOFUNC, SIGMOID, RELU, SOFTMAX};
enum loss_functions{MSE, BCE};

typedef struct netlayer_s netlayer_t;
typedef struct net_s net_t;
typedef struct config_s config_t;

struct netlayer_s{
    matrix_t* activations;
    matrix_t* weights;
    matrix_t* biases;
    matrix_t* sums;
    uint32_t nodes;
    netlayer_t* next_layer;
    enum activation_functions func;
};

struct net_s{
    uint32_t n_layers;
    netlayer_t* layer_iterator;
    netlayer_t* layers;
};

struct config_s{
    uint32_t epochs;
    uint32_t batch_size;
    double learning_rate;
};

net_t* network_init();
void add_layer(net_t* network, uint32_t nodes, enum activation_functions func);
netlayer_t* netlayer_init(uint32_t input_nodes);

void network_destroy(net_t* network);
void netlayer_destroy(netlayer_t* layer);

config_t* config_init(uint32_t epochs, uint32_t batch_size, double learning_rate);

void train(net_t* net, dataloader_t* dataloader, config_t* config);
void test(net_t* net, dataloader_t* dataloader, config_t* config);
void forward(net_t* net);
void backward(net_t* net);