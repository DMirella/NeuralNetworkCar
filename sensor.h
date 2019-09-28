#pragma once

#include <QGraphicsLineItem>
#include "map.h"

class Map;
enum Danger{Green = 0, Red};

class Sensor : public QGraphicsLineItem
{
public:

    Sensor(Map *map, float vectorX, float vectorY, float startPointX, float startPointY, int length);

    float distance();
    void setLevelDanger(Danger danger);
private:
    float vectorX, vectorY, startPointX, startPointY;
    int length;

    Map *map;
};
