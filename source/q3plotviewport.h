#ifndef Q3PLOTVIEWPORT_H
#define Q3PLOTVIEWPORT_H

#include <QWidget>
#include <QPaintEvent>

class Q3PlotFrame;

class Q3PlotViewport : public QWidget
{
    Q_OBJECT
public:
    explicit Q3PlotViewport(Q3PlotFrame &view);

signals:

public slots:
    void paintEvent(QPaintEvent *event);

private:
    Q3PlotFrame &view_;
};

#endif // Q3PLOTVIEWPORT_H
