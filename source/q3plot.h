#ifndef Q3PLOT_H
#define Q3PLOT_H

#include <QWidget>
#include <QGraphicsView>

#include "q3plotview.h"

namespace Ui {
class Q3Plot;
}

class Q3Plot : public QWidget
{
    Q_OBJECT

public:
    explicit Q3Plot(Q3PlotScene *scene, QWidget *parent = 0);
    explicit Q3Plot(Q3PlotView *view, QWidget *parent = 0);
    ~Q3Plot();

private:
    void init();

    Ui::Q3Plot *ui;
    Q3PlotView *view_;
};

#endif // Q3PLOT_H
