#pragma once

#include <QObject>
#include <QVector>

#include "car.h"
#include "neuralnetwork.h"

class Car;

class GameJudge
{
public:
    GameJudge(const QVector<Car*>& cars);
    void onWallCollision(Car* car);
private:
    QVector<Car*> cars;
    int countDeadOfGeneration;
};

