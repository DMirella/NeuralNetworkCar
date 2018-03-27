#include "neuralnetwork.h"

#include <QDebug>

NeuralNetwork::NeuralNetwork(int countHiddenLayers, int countInput, int countOutput, int countHidden)
{
    this->countHiddenLayers = countHiddenLayers;
    this->countInput        = countInput;
    this->countOutput       = countOutput;
    this->countHidden       = countHidden;

    hidden.append(NeuronLayer(this->countHidden, countInput));
    for(int i = 1; i < this->countHiddenLayers; i++){
        hidden.append(NeuronLayer(this->countHidden, countHidden));
    }
    output = NeuronLayer(countOutput, countHidden);
}

Action NeuralNetwork::think(double leftDist, double rightDist, double accelerate)
{
    QVector<double> inputs, outputs;
    inputs.append(leftDist);
    inputs.append(rightDist);
    inputs.append(accelerate);

    for(int i = 0; i < countHiddenLayers; i++){
        outputs = hidden[i].outputs(inputs);
        inputs = outputs;
    }
    outputs = output.outputs(inputs);

    double maxValue = outputs.at(0);
    int ind = 0;
    for(int i = 0; i < countOutput; i++){
        if(maxValue > outputs.at(i)){
            ind = i;
            maxValue = outputs.at(i);
        }
    }

    return Action(ind);
}
