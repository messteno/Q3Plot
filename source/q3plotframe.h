#ifndef Q3PLOTFRAME_H
#define Q3PLOTFRAME_H

#include <QWidget>
#include <QPainter>
#include "q3plotviewport.h"

//class Q3PlotFrameContainer
//{
//public:
//    enum LogicalPosition
//    {
//        LogicalTop = 1,
//        LogicalRight = 2,
//        LogicalBottom = 3,
//        LogicalLeft = 4,
//    };

//private:

//};

class Q3PlotFrame : public QWidget
{
    Q_OBJECT
public:
    explicit Q3PlotFrame(QWidget *parent = 0);
    virtual ~Q3PlotFrame();

    Q3PlotViewport *viewport() const;
    virtual void drawViewport(QPainter &painter);
    virtual void moveViewport(const QPoint &diff);
    void layoutChildren();

signals:

public slots:
    bool event(QEvent *event);

protected:
    Q3PlotViewport *viewport_;
};

#endif // Q3PLOTFRAME_H
