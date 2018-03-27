#ifndef CAR_H
#define CAR_H

#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>

#include "sensor.h"
#include "map.h"
#include "computerplayer.h"

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

private:
    void updateDangerSensor(Sensor *);

    float x, y;
    const float startX, startY;
    float xSpeed, ySpeed, rotationSpeed, acceleration, angle;
    Sensor *leftSensor, *rightSensor;

    QGraphicsRectItem *carcassRect, *windowRect;
    Map *map;
    ComputerPlayer *player;
    // QGraphicsItem interface
public:
    void advance(int phase);

    // QGraphicsItem interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // CAR_H
