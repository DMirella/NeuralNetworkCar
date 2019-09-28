#include "car.h"
#include <QBrush>
#include <QKeyEvent>
#include <QDebug>

#include <cmath>
#include <algorithm>

#include "computerplayer.h"

#define CAR_WIDTH   22
#define CAR_HEIGHT  40

#define ROTAION_CAR_SPEED 5
#define CAR_ACCELERATION  (5./60.)
#define MAX_CAR_TOTAL_SPEED 5.
#define SENSOR_LENGTH     100
#define SENSOR_ANGLE      110.

#define RED_ZONE    30

#define eps     1e-3

float toRadians(float angle){
    return angle * M_PI / 180.;
}

Car::Car(Map *map, float x, float y)
    : QGraphicsItemGroup(),
      xSpeed(0), ySpeed(0), rotationSpeed(0),
      acceleration(0), angle(90), startX(x), startY(y), distanceCountPerLife(0),
      isCarCrushed(false)
{
    this->x = x;
    this->y = y;
    this->map = map;

    player = new ComputerPlayer(this);

    carcassRect = new QGraphicsRectItem();
    windowRect  = new QGraphicsRectItem();
    rightSensor = new Sensor(this->map, cos(toRadians(SENSOR_ANGLE)), sin(toRadians(SENSOR_ANGLE)),
                              this->x, this->y + CAR_HEIGHT, SENSOR_LENGTH);
    leftSensor  = new Sensor(this->map, cos(toRadians(180 - SENSOR_ANGLE)), sin(toRadians(180 - SENSOR_ANGLE)),
                              this->x + CAR_WIDTH, this->y + CAR_HEIGHT, SENSOR_LENGTH);

    carcassRect->setBrush(Qt::red);
    carcassRect->setRect(this->x, this->y, CAR_WIDTH, CAR_HEIGHT);

    windowRect->setBrush(Qt::blue);
    int windowHeight = 10;
    int windowWidth = 3./4. * CAR_WIDTH;
    int windowTab = (CAR_WIDTH - windowWidth) / 2;
    windowRect->setRect(this->x + windowTab, this->y + CAR_HEIGHT - windowTab - windowHeight
                        , windowWidth, windowHeight);

    addToGroup(carcassRect);
    addToGroup(windowRect);
    addToGroup(rightSensor);
    addToGroup(leftSensor);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    qDebug() << this->x << " " << this->y;
    setTransformOriginPoint(this->x + CAR_WIDTH / 2, this->y + CAR_HEIGHT / 2);
}

void Car::putOnStart()
{
    xSpeed = 0;
    ySpeed = 0;
    rotationSpeed = 0,
    acceleration = 0;
    angle = 90;
    x = startX;
    y = startY;
    distanceCountPerLife = 0;
    isCarCrushed = false;
    acceleration = CAR_ACCELERATION;
    setPos(x, y);
}

CarParameters Car::info()
{
    CarParameters res;
    res.acceleration = acceleration;
    res.leftDist     = leftSensor->distance();
    res.rightDist    = rightSensor->distance();
    return res;
}

void Car::turnLeft()
{
    rotationSpeed = -ROTAION_CAR_SPEED;
}

void Car::turnRight()
{
    rotationSpeed = ROTAION_CAR_SPEED;
}

void Car::accelerate()
{
    acceleration = CAR_ACCELERATION;
}

void Car::brake()
{
  acceleration = CAR_ACCELERATION;
    //acceleration = -CAR_ACCELERATION;
}

void Car::advance(int phase)
{
    if(phase && !isCarCrushed) {
        moveBy(xSpeed, ySpeed);
        setRotation(angle - 90);
    } else if (!isCarCrushed) {
        player->makeStep();
        /********************************/
        acceleration = CAR_ACCELERATION;

        angle += rotationSpeed;

        float totalSpeed = std::min(std::max(sqrt(xSpeed * xSpeed + ySpeed * ySpeed) + acceleration, 0.)
                                    , MAX_CAR_TOTAL_SPEED);
        totalSpeed += 1. / (rand() % 2 + 1);
        xSpeed = totalSpeed * cos(toRadians(angle));
        ySpeed = totalSpeed * sin(toRadians(angle));
        rotationSpeed = 0;
        distanceCountPerLife++;

        float lDist = leftSensor->distance();
        float rDist = rightSensor->distance();

        if(lDist <= RED_ZONE){
            leftSensor->setLevelDanger(Red);
        }
        else{
            leftSensor->setLevelDanger(Green);
        }
        if(rDist <= RED_ZONE){
            rightSensor->setLevelDanger(Red);
        }
        else{
            rightSensor->setLevelDanger(Green);
        }

        if(lDist <= eps || rDist <= eps){
            isCarCrushed = true;
            map->wallCollision(this);
        }
    }
}

void Car::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_W:
        accelerate();
        break;
    case Qt::Key_S:
        brake();
        break;
    case Qt::Key_A:
        turnLeft();
        break;
    case Qt::Key_D:
        turnRight();
        break;
    }
}
