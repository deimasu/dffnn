#ifndef INPUTNEURON_H
#define INPUTNEURON_H

#include "Neuron.h"

class InputNeuron : public Neuron {
public:
        InputNeuron();
        void Activation() override;
};

#endif // INPUTNEURON_H
