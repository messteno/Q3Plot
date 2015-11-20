#ifndef Q3PLOTITEM_H
#define Q3PLOTITEM_H

#include <QTransform>
#include <QPainter>
#include <QObject>

class Q3PlotItem : public QObject
{
    Q_OBJECT
public:
    explicit Q3PlotItem(QObject *parent = 0);
    virtual void draw(QPainter &painter) = 0;

signals:

public slots:

protected:
    QTransform sceneTransform_;
};

class Q3PlotItemPoint : public Q3PlotItem
{
    Q_OBJECT
public:
    Q3PlotItemPoint(QPointF point, QObject *parent = 0);
    virtual void draw(QPainter &painter);

private:
    QPointF point_;
};

#endif // Q3PLOTITEM_H
