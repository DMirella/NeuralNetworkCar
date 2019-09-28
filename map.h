#pragma once

#include <QPixmap>
#include <QGraphicsScene>
#include <QRgb>
#include <QTimer>
#include <QVector>

#include "gamejudge.h"

class Car;
class GameJudge;
class Map : public QGraphicsScene
{
public:
    Map(QString path);
    ~Map();
    void wallCollision(Car *car);
    QRgb pixel(QPointF pt) const;
private:
    QVector<Car*> cars;
    QPixmap *map;
    GameJudge *gameJudge;
    QTimer *animationTimer;
};
