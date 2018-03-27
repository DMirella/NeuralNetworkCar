#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "neuralnetwork.h"
#include "car.h"

class Car;
class ComputerPlayer
{
public:
    ComputerPlayer(){}
    ComputerPlayer(Car *car);
    void makeStep();
private:
    NeuralNetwork ai;
    Car *car;
    CarParameters prevInfo;
};

#endif // COMPUTERPLAYER_H
