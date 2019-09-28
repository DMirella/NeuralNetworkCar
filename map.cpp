#include "map.h"
#include <QDebug>

#define GENERATION_COUNT 50

Map::Map(QString path)
    : QGraphicsScene()
{
    map = new QPixmap(path);
    addPixmap(*map);
    for (int i = 0; i < GENERATION_COUNT; i++) {
        cars.push_back(new Car(this, 10, 10));
        addItem(cars[i]);
    }

    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(advance()));
    animationTimer->start(1000/60);

    gameJudge = new GameJudge(cars);

    QGraphicsRectItem *r =  new QGraphicsRectItem;
    r->setRect(0, 0, width(), height());
    addItem(r);
}

Map::~Map()
{
    delete gameJudge;
}

void Map::wallCollision(Car* car)
{
    gameJudge->onWallCollision(car);
}

QRgb Map::pixel(QPointF pt) const
{
    return map->toImage().pixel(pt.toPoint());
}
