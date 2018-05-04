#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "inputneuron.h"
#include "trainingsample.h"

class NeuralNetwork {
public:
        NeuralNetwork(std::vector<int> layers_configuration);
        ~NeuralNetwork();

        float Process(std::vector<float> inputs);
        void AddTrainingSample(TrainingSample sample);
        void Train();
        float DerivativeFromTanh(float value);

        std::vector<std::vector<Neuron*>> layers;
        std::vector<TrainingSample> training_set;
        float learning_rate;
        int epoch;
        float loss;
};


#endif // NEURALNETWORK_H
