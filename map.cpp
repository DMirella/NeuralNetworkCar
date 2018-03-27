#include "map.h"
#include <QDebug>

Map::Map(QString path)
    : QGraphicsScene()
{
    car = new Car(this, 0, 0);
    map = new QPixmap(path);
    addPixmap(*map);
    addItem(car);

    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(advance()));
    animationTimer->start(1000/60);

    gameJudge = new GameJudge(car);

    QGraphicsRectItem *r =  new QGraphicsRectItem;
    r->setRect(0, 0, width(), height());
    addItem(r);
}

Map::~Map()
{
    delete gameJudge;
}

void Map::wallCollision()
{
    gameJudge->onWallCollision();
}

QRgb Map::pixel(QPointF pt) const
{
    return map->toImage().pixel(pt.toPoint());
}
