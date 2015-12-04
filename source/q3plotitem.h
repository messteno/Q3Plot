#ifndef Q3PLOTITEM_H
#define Q3PLOTITEM_H

#include <QTransform>
#include <QPainter>
#include <QObject>
#include <QVector>

class Q3PlotItem : public QObject
{
    Q_OBJECT
public:
    explicit Q3PlotItem(QObject *parent = 0);
    virtual void draw(QPainter &painter) = 0;
};

class Q3PlotItemPoint : public Q3PlotItem
{
    Q_OBJECT
public:
    Q3PlotItemPoint(QPointF point, QObject *parent = 0);
    virtual void draw(QPainter &painter);

    static const int PointSize = 5;

protected:
    QPointF point_;
};

class Q3PlotItemGraph : public Q3PlotItem
{
    Q_OBJECT
public:
    Q3PlotItemGraph(const QVector<QPointF> &data, QObject *parent = 0);
    virtual void draw(QPainter &painter);

protected:
    QVector<QPointF> data_;
};

#endif // Q3PLOTITEM_H
