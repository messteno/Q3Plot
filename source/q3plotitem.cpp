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

    painter.drawEllipse(point_, PointSize / sx, PointSize / sy);
    painter.restore();
}

Q3PlotItemGraph::Q3PlotItemGraph(const QVector<QPointF> &data, QObject *parent) :
    Q3PlotItem(parent),
    data_(data)
{

}

void Q3PlotItemGraph::draw(QPainter &painter)
{
    painter.save();

    int segmentStart = 0;
    int i = 0;
    const int lineDataSize = data_.size();
    while (i < lineDataSize)
    {
        if (qIsNaN(data_.at(i).y()) || qIsNaN(data_.at(i).x()))
        {
            painter.drawPolyline(data_.constData() + segmentStart,
                                 i - segmentStart);
            segmentStart = i + 1;
        }
        ++i;
    }
    painter.drawPolyline(data_.constData() + segmentStart,
                         lineDataSize - segmentStart);

    painter.restore();
}
