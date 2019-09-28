#include "neuron.h"

#include <cmath>
#include <cstdlib>
#include <QDebug>

#define MUTATION_CHANCE 1

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

Neuron Neuron::merge(const Neuron& other) {
    Neuron res = *this;
    int rand_1 = rand() % weights.size();
    for (int i = 0; i < rand_1; i++) {
        res.weights[i] = other.weights[i];
        if (rand() % 100 + 1 <= MUTATION_CHANCE) {
          qDebug() << "MUTATION_CHANCEMUTATION_CHANCEMUTATION_CHANCEMUTATION_CHANCEMUTATION_CHANCEMUTATION_CHANCEMUTATION_CHANCE";
            res.weights[i] = floatRand();
        }
    }
    qDebug() << weights << endl << other.weights << endl << res.weights << endl << "-------------------------------------------------------------";
    return res;
}
