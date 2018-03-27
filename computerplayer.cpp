#include "computerplayer.h"

#define COUNT_HIDDEN_LAYERS 1
#define COUNT_INPUT         3
#define COUNT_OUTPUT        4
#define COUNT_HIDDEN        5

ComputerPlayer::ComputerPlayer(Car *car)
{
    this->car = car;
    ai = NeuralNetwork(COUNT_HIDDEN_LAYERS, COUNT_INPUT, COUNT_OUTPUT, COUNT_HIDDEN);
}

void ComputerPlayer::makeStep()
{
    CarParameters info = car->info();
    Action action = ai.think(info.leftDist, info.rightDist, info.acceleration);
    switch(action){
    case TurnLeft:
        car->turnLeft();
        break;
    case TurnRight:
        car->turnRight();
        break;
    case Accelerate:
        car->accelerate();
        break;
    case Brake:
        car->brake();
        break;
    }
}
