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
    scene->addItem(p1);
    scene->addItem(p2);

    QVector<QPointF> data2D;
    for (int i = 0; i <= 10000; ++i) {
        qreal x = i / 10000. - 0.5;
        qreal y = 4. * (0.5 - x) * (x + 0.5) + 0.25;
        data2D.append(QPointF(x, y));
    }
    Q3PlotItemGraph *graph = new Q3PlotItemGraph(data2D);
    scene->addItem(graph);

    Q3PlotView *view = new Q3PlotView(scene, this);
    view->setAspectRatioMode(Qt::IgnoreAspectRatio);
    view->setSceneRect(QRectF(-1, -0.5, 2., 2.));
    view->addAxis(Q3PlotFrame::PositionLeft);
    view->addAxis(Q3PlotFrame::PositionTop)->setLabelsVisible(false);
    view->addAxis(Q3PlotFrame::PositionRight)->setLabelsVisible(false);
    view->addAxis(Q3PlotFrame::PositionBottom);

    view->addColorBar(Q3PlotFrame::PositionRight, -10, 10)->setLabelsVisible(false);

    Q3Plot *plot = new Q3Plot(view, this);
    this->setCentralWidget(plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
