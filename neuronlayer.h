#pragma once
#include "neuron.h"

class NeuronLayer
{
public:
    NeuronLayer(){}
    NeuronLayer(int countNeurons, int countPrevNeurons);
    QVector<double> outputs(QVector<double> inputs);

    NeuronLayer merge(const NeuronLayer& other);
private:
    int countNeurons;
    QVector<Neuron> neurons;
};

