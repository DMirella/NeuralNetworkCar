#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "neuronlayer.h"

enum Action{Accelerate = 0, Brake, TurnLeft, TurnRight};

class NeuralNetwork
{
public:
    NeuralNetwork(){}
    NeuralNetwork(int countHiddenLayers, int countInput, int countOutput, int countHidden);
    Action think(double leftDist, double rightDist, double accelerate);
private:
    int countHiddenLayers, countInput, countOutput, countHidden;
    QVector<NeuronLayer> hidden;
    NeuronLayer output;
};

#endif // NEURALNETWORK_H
