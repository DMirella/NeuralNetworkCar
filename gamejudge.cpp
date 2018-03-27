#include "gamejudge.h"

#include <QDebug>
#include <QObject>
#include <QMessageBox>

GameJudge::GameJudge(Car *car)
{
    this->car = car;
}

void GameJudge::onWallCollision()
{
    car->putOnStart();
}
