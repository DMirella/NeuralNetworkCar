#ifndef MAP_H
#define MAP_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QRgb>
#include <QTimer>

#include "car.h"
#include "gamejudge.h"

class Car;
class GameJudge;
class Map : public QGraphicsScene
{
public:
    Map(QString path);
    ~Map();
    void wallCollision();
    QRgb pixel(QPointF pt) const;
private:
    Car *car;
    QPixmap *map;
    GameJudge *gameJudge;
    QTimer *animationTimer;
};

#endif // MAP_H
