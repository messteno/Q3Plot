#include <QTransform>
#include <QDebug>

#include "q3plotitem.h"

Q3PlotItem::Q3PlotItem(QObject *parent) :
    QObject(parent)
{

}

Q3PlotItemPoint::Q3PlotItemPoint(QPointF point, QObject *parent) :
    Q3PlotItem(parent),
    point_(point)
{

}

void Q3PlotItemPoint::draw(QPainter &painter)
{
    painter.save();
    qreal sx = painter.transform().m11();
    qreal sy = painter.transform().m22();

    painter.drawEllipse(point_, 5 / sx, 5 / sy);
    painter.restore();
}
