#include <QGraphicsView>

#include "q3plotitem.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Q3PlotScene *scene = new Q3PlotScene(QRectF(), this);
    Q3PlotItemPoint *p1 = new Q3PlotItemPoint(QPointF(0.25, 0.25), scene);
    Q3PlotItemPoint *p2 = new Q3PlotItemPoint(QPointF(0.75, 0.75), scene);
//    Q3PlotItemPoint *p2 = new Q3PlotItemPoint(QPointF(-0.5, -0.5), scene);
    scene->addItem(p1);
    scene->addItem(p2);

    Q3PlotView *view = new Q3PlotView(scene, this);
    view->setConstraints(Q3PlotScene::FitInViewConstraints);
    view->setSceneRect(QRectF(0., 0, 1, 1));

    Q3Plot *plot = new Q3Plot(view, this);
    this->setCentralWidget(plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
