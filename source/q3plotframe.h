#ifndef Q3PLOTFRAME_H
#define Q3PLOTFRAME_H

#include <QWidget>
#include <QPainter>
#include <QList>

#include "q3plotviewport.h"

class Q3PlotFrameContainer
{
public:
    enum Position
    {
        Top = 1,
        Right = 2,
        Bottom = 3,
        Left = 4,
    };

    Q3PlotFrameContainer();

private:
    QList<QWidget *> widgets_;
};

class Q3PlotFrame : public QWidget
{
    Q_OBJECT
public:
    explicit Q3PlotFrame(QWidget *parent = 0);
    virtual ~Q3PlotFrame();

    Q3PlotViewport *viewport() const;
    virtual void drawViewport(QPainter &painter);
    virtual void moveViewport(const QPoint &diff);
    virtual void scaleViewport(const QPoint &pos, qreal scale);
    void layoutChildren();

signals:

public slots:
    bool event(QEvent *event);

protected:
    Q3PlotViewport *viewport_;
};

#endif // Q3PLOTFRAME_H
