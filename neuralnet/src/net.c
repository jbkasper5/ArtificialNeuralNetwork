#include "net.h"

net_t* network_init(uint32_t input_nodes){
    net_t* net = (net_t*)malloc(sizeof(net_t*));
    net->n_layers = 0;
    add_layer(net, input_nodes, NOFUNC);
    return net;
}

void add_layer(net_t* network, uint32_t input_nodes, enum activation_functions func){
    if(network->n_layers == 0){
        network->layers = netlayer_init(input_nodes);
        network->layer_iterator = network->layers;
    }else{
        netlayer_t* layer = netlayer_init(input_nodes);
        layer->func = func;
        layer->weights = he_weight_matrix(network->layer_iterator->nodes, input_nodes);
        layer->biases = he_bias_matrix(input_nodes);
        network->layer_iterator->next_layer = layer;
        network->layer_iterator = layer;
    }
    network->n_layers++;
}

netlayer_t* netlayer_init(uint32_t nodes){
    netlayer_t* layer = malloc(sizeof(netlayer_t));
    layer->next_layer = NULL;
    layer->activations = zero_matrix(nodes, 1);
    layer->sums = zero_matrix(nodes, 1);
    layer->weights = NULL;
    layer->biases = NULL;
    layer->func = NOFUNC;
    layer->nodes = nodes;
    return layer;
}

void network_destroy(net_t* network){
    netlayer_t* next_layer = NULL;
    P("Destroying network with %d layers.\n", network->n_layers);
    for(int i = 0; i < network->n_layers; ++i){
        next_layer = network->layers->next_layer;
        netlayer_destroy(network->layers);
        P("Destroyed layer %d\n", (i + 1));
        network->layers = next_layer;
    }
    free(network);
}

void netlayer_destroy(netlayer_t* layer){
    if(layer->activations) matrix_destroy(layer->activations);
    if(layer->weights) matrix_destroy(layer->weights);
    if(layer->biases) matrix_destroy(layer->biases);
    if(layer->sums) matrix_destroy(layer->sums);
    free(layer);
}