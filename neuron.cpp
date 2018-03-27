#include "neuron.h"

#include <cmath>
#include <cstdlib>
#include <QDebug>


double floatRand(){
    return ((double)rand()) / RAND_MAX - 0.5;
}

Neuron::Neuron(int countPrevNeurons)
{
    this->countPrevNeurons = countPrevNeurons;

    for(int i = 0; i < this->countPrevNeurons; i++){
        double w = floatRand();
        qDebug() << w;
        weights.append(w);
    }
}

double Neuron::adder(QVector<double> inputs)
{
    double res = 0;
    for(int i = 0; i < countPrevNeurons; i++){
        res += (weights.at(i) * inputs.at(i));
    }
    return res;
}

double Neuron::activationFunction(double sum, bool inverse)
{
    if(inverse){
        return (1 - activationFunction(sum)) * activationFunction(sum);
    }
    else{
        return 1. / (1. + exp(-sum));
    }
}

double Neuron::output(QVector<double> inputs)
{
    return activationFunction(adder(inputs));
}
