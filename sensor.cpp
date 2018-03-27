#include "sensor.h"

#include <cmath>
#include <QPen>
#include <QDebug>

#define SENSOR_WIDTH 2

Sensor::Sensor(Map *map, float vectorX, float vectorY, float startPointX, float startPointY, int length)
    : QGraphicsLineItem()
{
    this->vectorX = vectorX;
    this->vectorY = vectorY;
    this->startPointX = startPointX;
    this->startPointY = startPointY;
    this->length = length;
    this->map = map;

    setPen(QPen(Qt::gray, SENSOR_WIDTH, Qt::DotLine));
    setLine(startPointX, startPointY, startPointX + vectorX * length, startPointY + vectorY * length);
}

float Sensor::distance()
{
    QPointF stpt = mapToScene(QPointF(line().p1())), fnpt = mapToScene(QPointF(line().p2()));
    QPointF curpt = stpt;
    float kx = (fnpt.x() - stpt.x()) / length;
    float ky = (fnpt.y() - stpt.y()) / length;

    for(float i = 0; i < length; i++){
        QColor cur = QColor(map->pixel(curpt));
        int curc = (cur.red() + cur.green() + cur.blue()) / 3;
        int etalon = (127 + 127 + 127) / 3;

        if(curc <= etalon){
            float dist = sqrt((curpt.x() - stpt.x()) * (curpt.x() - stpt.x())
                              + (curpt.y() - stpt.y()) * (curpt.y() - stpt.y()));
            return dist;
        }

        curpt.setX(curpt.x() + kx);
        curpt.setY(curpt.y() + ky);
    }

    return INFINITY;
}

void Sensor::setLevelDanger(Danger danger)
{
    switch (danger) {
    case Green:
        setPen(QPen(Qt::green, SENSOR_WIDTH, Qt::DotLine));
        break;
    case Red:
        setPen(QPen(Qt::red, SENSOR_WIDTH, Qt::DotLine));
        break;
    default:
        break;
    }
}
