#include "neuronlayer.h"

#include <QDebug>

#include "neuron.h"

NeuronLayer::NeuronLayer(int countNeurons, int countPrevNeurons)
{
    this->countNeurons = countNeurons;
    for(int i = 0; i < this->countNeurons; i++){
        neurons.append(Neuron(countPrevNeurons));
    }
}

QVector<double> NeuronLayer::outputs(QVector<double> inputs)
{
    QVector<double> res;
    for(int i = 0; i < countNeurons; i++){
        res.append(neurons[i].output(inputs));
    }
    return res;
}

NeuronLayer NeuronLayer::merge(const NeuronLayer& other) {
    NeuronLayer res = *this;
    for (int i = 0; i < neurons.size(); i++) {
        res.neurons[i] = res.neurons[i].merge(other.neurons[i]);
    }
    return res;
}
