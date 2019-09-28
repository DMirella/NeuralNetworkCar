#include "gamejudge.h"

#include <QDebug>
#include <QObject>
#include <QVector>
#include <QMessageBox>

#include <cstdlib>

#include "computerplayer.h"
#include "neuralnetwork.h"
#include "car.h"

GameJudge::GameJudge(const QVector<Car*>& cars)
{
    this->cars = cars;
    countDeadOfGeneration = 0;
}

void GameJudge::onWallCollision(Car* car)
{
    //car->putOnStart();
    qDebug() << countDeadOfGeneration << endl;
    countDeadOfGeneration++;
    if (countDeadOfGeneration >= cars.size()) {
        QVector<NeuralNetwork> new_ais;
        int distance_sum = 0;
        for (auto it : cars) {
          distance_sum += it->getDistanceCountPerLife();
        }
        int l = 0, r = (int)(((float)cars[0]->getDistanceCountPerLife() / distance_sum) * 100);
        float cc = 0;
        for(int i = 0; i < cars.size(); i++) {
          cc += ((float)cars[i]->getDistanceCountPerLife() / distance_sum);
          qDebug() <<cc << " " << ((float)cars[i]->getDistanceCountPerLife() / distance_sum) << " " << distance_sum << " " << cars[i]->getDistanceCountPerLife() << " " << l << " " << r;

          l = r;
          if (i + 1 >= cars.size()) break;
          r += (int)(((float)cars[i + 1]->getDistanceCountPerLife() / distance_sum) * 100);
        }
        for (int i = 0; i < cars.size(); i++) {
            int rand_1001 = rand() % 100 + 1, rand_1002 = rand() % 100 + 1;
            Car* ind1 = cars[0];
            Car* ind2 = cars[0];
            int l = 0, r = (int)(((float)cars[0]->getDistanceCountPerLife() / distance_sum) * 100);
            for(int i = 0; i < cars.size(); i++) {
             // qDebug() << ((float)cars[i]->getDistanceCountPerLife() / distance_sum) << " " << distance_sum << " " << cars[i]->getDistanceCountPerLife() << " " << l << " " << r;
              if(l <= rand_1001 && rand_1001 <= r) {
                  ind1 = cars[i];
                  qDebug() << "CHOSEN1 " << i;
                  break;
              }
              l = r + 1;
              if (i + 1 >= cars.size()) break;
              r += (int)(((float)cars[i + 1]->getDistanceCountPerLife() / distance_sum) * 100);
              if (l > r) l = r;
            }
            l = 0; r = (int)(((float)cars[0]->getDistanceCountPerLife() / distance_sum) * 100);
            for(int i = 0; i < cars.size(); i++) {
              if(l <= rand_1002 && rand_1002 <= r) {
                  ind2 = cars[i];
                  qDebug() << "CHOSEN2 " << i;
                  break;
              }
              l = r + 1;
              if (i + 1 >= cars.size()) break;
              r += (int)(((float)cars[i + 1]->getDistanceCountPerLife() / distance_sum) * 100);
              if (l > r) l = r;
            }
            new_ais.push_back(ind1->player->ai.merge(ind2->player->ai));
        }

        for (int i = 0; i < new_ais.size(); i++) {
            cars[i]->player->ai = new_ais[i];
        }

        countDeadOfGeneration = 0;
        for (auto it : cars) {
            it->putOnStart();
        }
    }
}
