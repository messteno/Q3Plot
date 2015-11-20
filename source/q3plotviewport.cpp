#include <QPainter>
#include <QDebug>

#include "q3plotview.h"
#include "q3plotviewport.h"

Q3PlotViewport::Q3PlotViewport(Q3PlotFrame &view) :
    QWidget(&view),
    view_(view)
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
}

void Q3PlotViewport::mouseReleaseEvent(QMouseEvent *event)
{
    lastPressedMousePoint_ = QPoint();
}
