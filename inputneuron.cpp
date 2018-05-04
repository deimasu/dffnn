#include "inputneuron.h"

InputNeuron::InputNeuron()
{
    // setting bias to 0 in order to prevent input value from changing
    this->bias = 0;
}
// for input layer activation function is x => x
void InputNeuron::Activation()
{
    this->last_calculated = this->SumWeights();
}
