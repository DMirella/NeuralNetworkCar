#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLayout>
#include <QTimer>
#include "car.h"
#include "map.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *w = new QWidget(this);
    w->setLayout(ui->mainLay);
    setCentralWidget(w);

    map = new Map("C:/Users/Dima/Documents/qt/NeuralNetworkCar/maps/6.jpg");
    ui->graphicsView->setScene(map);
}

MainWindow::~MainWindow()
{
    delete ui;
}
