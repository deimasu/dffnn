#include "neuralnetwork.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>

NeuralNetwork::NeuralNetwork(std::vector<int> layers_configuration)
{
    // setting learning rate coefficient to 0.03
    this->learning_rate = 0.03;
    // epoch is 0 by default and changes after each train iteration
    this->epoch = 0;
    this->loss = 1;
    // create neurons according to given configuration
    int processed = 0;
    for (const auto& num_in_cur_layer : layers_configuration)
    {
        std::vector<Neuron*> neurons;
        for (int i = 0; i < num_in_cur_layer; i++)
        {
            neurons.push_back(processed == 0 ? new InputNeuron() : new Neuron());
        }
        this->layers.push_back(neurons);
        processed++;
    }

    // create the links between the neurons
    for (int i = 0; i < this->layers.size(); i++)
    {
        if (i == 0)
        {
            for (auto& neuron : this->layers[i])
            {
                // weight is always =1 for input layer input links
                neuron->input_links.push_back(new Link(1.0));
            }
        }
        else
        {
            for (auto& neuron_in_this_layer : this->layers[i])
            {
                for (auto& neuron_in_prev_layer : this->layers[i - 1]) {
                    // random between -1 and 1 for all non-input neurons
                    Link* temp = new Link((float)rand() / RAND_MAX * 2 - 1);
                    // linking the neurons
                    neuron_in_this_layer->input_links.push_back(temp);
                    neuron_in_prev_layer->output_links.push_back(temp);
                }
            }
        }
    }
}

void NeuralNetwork::AddTrainingSample(TrainingSample sample)
{
    this->training_set.push_back(sample);
}

// tanh derivative (for back propagation)
float NeuralNetwork::DerivativeFromTanh(float value)
{
    return 1.0f - value * value;
}

float NeuralNetwork::Process(std::vector<float> inputs)
{
    // do not process if number of inputs is not equal to input neurons count
    if (inputs.size() != this->layers[0].size()) return 0;
    // setting input values to input links of neurons of the 1st layer
    for (int i = 0; i < inputs.size(); i++)
    {
        layers[0][i]->input_links[0]->value = inputs[i];
    }

    int layers_processed = 0;
    // for each neuron layer by layer find sum of multi (value * weight) for each input link + bias
    // then send the result to the output links for neurons of next layer (if current layer is not the last)
    for (const auto& layer : this->layers)
    {
        for (const auto& neuron : layer)
        {
            neuron->Activation();
            if (layers_processed < this->layers.size() - 1)
            {
                neuron->SendToNextLayer();
            }
        }
        layers_processed++;
    }

    return this->layers[this->layers.size() - 1][0]->last_calculated;
}

void NeuralNetwork::ClearTrainingSet()
{
    std::vector<TrainingSample> new_set;
    training_set = new_set;
}

void NeuralNetwork::Train()
{
    float training_loss = 0;

    for (const auto& sample : this->training_set)
    {
        Neuron *output_neuron = this->layers[this->layers.size() - 1][0];
        float expected = sample.output;
        float actual = this->Process(sample.inputs);
        float err = expected - actual;

        training_loss += err;

        // calculating error from given expected result and actual network processing result
        float error = err * this->DerivativeFromTanh(actual);

        for (auto& link : output_neuron->input_links)
        {
            link->weight += this->learning_rate * error * link->value;
            link->error = error;
        }

        output_neuron->bias += this->learning_rate * error;

        for (int i = layers.size() - 2; i > 0; i--)
        {
            auto current_layer = this->layers[i];

            for (const auto& neuron : current_layer)
            {
                float error_sum = 0;

                for (const auto& link : neuron->output_links)
                {
                    error_sum += link->error * link->weight;
                }

                error = error_sum * this->DerivativeFromTanh(neuron->last_calculated);

                for (auto& link : neuron->input_links)
                {
                    link->weight += this->learning_rate * error * link->value;
                    link->error = error;
                }

                neuron->bias += this->learning_rate * error;
            }
        }

    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->training_set.begin(), this->training_set.end(), std::default_random_engine(seed));
    epoch++;

    training_loss /= this->training_set.size();
    loss = training_loss;
}

NeuralNetwork::~NeuralNetwork()
{
    for (auto& layer : layers)
    {
        for (int i = 0; i < layer.size(); i++)
        {
            for (int k = 0; k < layer[i]->input_links.size(); k++)
            {
                delete layer[i]->input_links[k];
            }
            delete layer[i];
        }
    }
}
