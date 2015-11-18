#include <QPainter>

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
