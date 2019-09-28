#pragma once
#include <QVector>

class Neuron
{
public:
    Neuron(){}
    Neuron(int countPrevNeurons);
    double adder(QVector<double> inputs);
    double activationFunction(double sum, bool inverse = false);
    double output(QVector<double> inputs);

    Neuron merge(const Neuron& other);
private:
    QVector<double> weights;
    int countPrevNeurons;
};
