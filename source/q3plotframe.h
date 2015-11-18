#ifndef Q3PLOTFRAME_H
#define Q3PLOTFRAME_H

#include <QWidget>
#include <QPainter>
#include "q3plotviewport.h"

class Q3PlotFrame : public QWidget
{
    Q_OBJECT
public:
    explicit Q3PlotFrame(QWidget *parent = 0);
    virtual ~Q3PlotFrame();

    Q3PlotViewport *viewport() const;
    virtual void drawViewport(QPainter &painter);
    void layoutChildren();

signals:

public slots:
    bool event(QEvent *event);

protected:
    Q3PlotViewport *viewport_;
};

#endif // Q3PLOTFRAME_H
