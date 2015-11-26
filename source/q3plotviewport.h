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
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    Q3PlotFrame &view_;
    QPoint lastPressedMousePoint_;
    qreal wheelDelta_;
};

#endif // Q3PLOTVIEWPORT_H
