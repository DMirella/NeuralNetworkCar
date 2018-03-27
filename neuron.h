#ifndef NEURON_H
#define NEURON_H

#include <QVector>

class Neuron
{
public:
    Neuron(){}
    Neuron(int countPrevNeurons);
    double adder(QVector<double> inputs);
    double activationFunction(double sum, bool inverse = false);
    double output(QVector<double> inputs);
private:
    QVector<double> weights;
    int countPrevNeurons;
};

#endif // NEURON_H
