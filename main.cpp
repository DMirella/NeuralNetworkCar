#include "mainwindow.h"
#include <QApplication>

#include <cstdio>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
