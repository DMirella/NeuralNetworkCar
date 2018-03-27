#ifndef GAMEJUDGE_H
#define GAMEJUDGE_H

#include <QObject>

#include "car.h"
#include "neuralnetwork.h"

class Car;

class GameJudge
{
public:
    GameJudge(Car *car);
    void onWallCollision();
private:
    Car *car;
};

#endif // GAMEJUDGE_H
