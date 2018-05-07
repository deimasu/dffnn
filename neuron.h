#ifndef NEURON_H
#define NEURON_H

#include "link.h"
#include <vector>

class Neuron {
public:
    std::vector<Link*> output_links;
    std::vector<Link*> input_links;
    Neuron();
    float bias;
    float last_calculated;


    virtual void Activation();
    float SumWeights();
    void SendToNextLayer();
};

#endif
