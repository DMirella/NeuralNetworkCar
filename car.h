#pragma once

#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>

#include "sensor.h"
#include "map.h"

struct CarParameters
{
    double leftDist, rightDist, acceleration;
    CarParameters() {}
};

class Map;
class Sensor;
class ComputerPlayer;
class Car : public QGraphicsItemGroup
{
public:
    Car(Map *map, float x, float y);
    void putOnStart();
    CarParameters info();

    void turnLeft();
    void turnRight();
    void accelerate();
    void brake();

    int getDistanceCountPerLife() const { return distanceCountPerLife; }

    ComputerPlayer *player;
private:
    void updateDangerSensor(Sensor *);

    float x, y;
    const float startX, startY;
    float xSpeed, ySpeed, rotationSpeed, acceleration, angle;
    Sensor *leftSensor, *rightSensor;

    QGraphicsRectItem *carcassRect, *windowRect;
    Map *map;

    int distanceCountPerLife;
    bool isCarCrushed;

    // QGraphicsItem interface
public:
    void advance(int phase);

    // QGraphicsItem interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

