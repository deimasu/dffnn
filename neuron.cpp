#include "neuron.h"
#include <cmath>

Neuron::Neuron()
{
        this->bias = 0.5f;
}
// main function of neuron = tanh(x)
void Neuron::Activation()
{
        float e2x = std::exp(2 * this->SumWeights());
        this->last_calculated = (e2x - 1) / (e2x + 1);
}
// sum (weitht[i] * value[i]) + bias
float Neuron::SumWeights()
{
        float sum = this->bias;
        for (const auto& link : this->input_links)
        {
                sum += link->value * link->weight;
        }
        return sum;
}
// setting the last calculated result of Neuron::Activation() to the links between this neuron and next layer neurons
void Neuron::SendToNextLayer()
{
        for (auto& link : this->output_links)
        {
                link->value = this->last_calculated;
        }
}
