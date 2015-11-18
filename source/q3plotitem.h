#ifndef Q3PLOTITEM_H
#define Q3PLOTITEM_H

#include <QPainter>
#include <QObject>

class Q3PlotItem : public QObject
{
    Q_OBJECT
public:
    explicit Q3PlotItem(QObject *parent = 0);
    virtual void paint(QPainter &painter) = 0;

signals:

public slots:
};

#endif // Q3PLOTITEM_H
