#include <QPainter>
#include <QDebug>
#include <math.h>

#include "q3plotview.h"
#include "q3plotviewport.h"

Q3PlotViewport::Q3PlotViewport(Q3PlotFrame &view) :
    QWidget(&view),
    view_(view),
    wheelDelta_(0)
{

}

void Q3PlotViewport::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    view_.drawViewport(painter);
    painter.end();
}

void Q3PlotViewport::mouseMoveEvent(QMouseEvent *event)
{
    if (!lastPressedMousePoint_.isNull())
    {
        QPoint diff = event->pos() - lastPressedMousePoint_;
        view_.moveViewport(diff);
    }

    lastPressedMousePoint_ = event->pos();
    setCursor(Qt::SizeAllCursor);
}

void Q3PlotViewport::mouseReleaseEvent(QMouseEvent *event)
{
    lastPressedMousePoint_ = QPoint();
    setCursor(Qt::ArrowCursor);
}

void Q3PlotViewport::wheelEvent(QWheelEvent *event)
{
    wheelDelta_ += event->delta();
    int numSteps = wheelDelta_ / 15 / 8;
    if (numSteps == 0)
    {
        event->ignore();
        return;
    }
    wheelDelta_ = 0;

    qreal scale = pow(0.9, numSteps);
    view_.scaleViewport(event->pos(), scale);
}
