#pragma once

#include "neuronlayer.h"

enum Action{TurnLeft = 0, TurnRight, Accelerate, Brake};

class NeuralNetwork
{
public:
    NeuralNetwork(){}
    NeuralNetwork(int countHiddenLayers, int countInput, int countOutput, int countHidden);
    Action think(double leftDist, double rightDist, double accelerate);

    NeuralNetwork merge(const NeuralNetwork& other);
private:
    int countHiddenLayers, countInput, countOutput, countHidden;
    QVector<NeuronLayer> hidden;
    NeuronLayer output;
};
