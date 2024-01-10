#include "net.h"

int main(int argc, char** argv){
    P("Init\n");
    uint32_t model_inputs = 28 * 28;
    net_t* net = network_init(model_inputs);
    add_layer(net, 5, SIGMOID);
    add_layer(net, 8, RELU);
    P("units in layer 2: %d\n", net->layer_iterator->nodes);
    show(net->layer_iterator->weights);
    network_destroy(net);
    return 0;
}