#include <QGraphicsView>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Q3PlotScene *scene = new Q3PlotScene(QRectF(-1, 1, 2, 2), this);
    Q3Plot *plot = new Q3Plot(scene, this);
    this->setCentralWidget(plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
