#pragma once

#include "neuralnetwork.h"
#include "car.h"

class Car;
class ComputerPlayer
{
public:
    ComputerPlayer(){}
    ComputerPlayer(Car *car);
    void makeStep();

    NeuralNetwork ai;
private:
    Car *car;
    CarParameters prevInfo;
};
