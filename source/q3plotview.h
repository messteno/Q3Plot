#ifndef Q3PLOTVIEW_H
#define Q3PLOTVIEW_H

#include <QWidget>
#include <iostream>

#include "q3plotscene.h"
#include "q3plotframe.h"

class Q3PlotView : public Q3PlotFrame
{
    Q_OBJECT
    Q_PROPERTY(QBrush backgroundBrush READ backgroundBrush WRITE setBackgroundBrush)

public:
    explicit Q3PlotView(Q3PlotScene *scene, QWidget *parent = 0);
    ~Q3PlotView();

    void drawBackground(QPainter &painter, const QRectF &rect);
    void drawViewport(QPainter &painter);

    QBrush backgroundBrush() const;
    void setBackgroundBrush(const QBrush &brush);

signals:
public slots:
    void paintEvent(QPaintEvent *event);

public:
    Q3PlotScene *scene_;
    QBrush backgroundBrush_;
};

#endif
