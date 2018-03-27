#ifndef NEURONLAYER_H
#define NEURONLAYER_H

#include "neuron.h"

class NeuronLayer
{
public:
    NeuronLayer(){}
    NeuronLayer(int countNeurons, int countPrevNeurons);
    QVector<double> outputs(QVector<double> inputs);
private:
    int countNeurons;
    QVector<Neuron> neurons;
};

#endif // NEURONLAYER_H
