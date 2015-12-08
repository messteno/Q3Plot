#ifndef Q3PLOTVIEW_H
#define Q3PLOTVIEW_H

#include <QWidget>
#include <iostream>

#include "q3plotscene.h"
#include "q3plotframe.h"
#include "q3plotaxis.h"
#include "q3plotcolorbar.h"

class Q3PlotView : protected Q3PlotFrame
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(int tickLength READ tickLength WRITE setTickLength)
    friend class Q3Plot;

public:
    explicit Q3PlotView(Q3PlotScene *scene, QWidget *parent = 0);
    ~Q3PlotView();

    virtual void drawViewport(QPainter &painter);
    virtual void moveViewport(const QPoint &diff);
    virtual void scaleViewport(const QPoint &pos, qreal scale);

    QPointF mapToScene(const QPoint &point);
    QPoint mapFromScene(const QPointF &point);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    int tickLength() const;
    void setTickLength(int tickLength);

    void setAspectRatioMode(Qt::AspectRatioMode aspectRatioMode);

    virtual QSize sizeHint() const;

    Q3PlotAxis* axis(Q3PlotFrame::LogicalPosition axisPosition);
    Q3PlotAxis *addAxis(Q3PlotFrame::LogicalPosition axisPosition);
    bool hasAxis(Q3PlotFrame::LogicalPosition axisPosition);
//    void removeAxis(Q3PlotFrame::LogicalPosition axisPosition);

    Q3PlotColorBar* addColorBar(Q3PlotFrame::LogicalPosition colorBarPosition,
                                qreal lower, qreal upper);
    void layoutAndFit();

signals:
    void sceneRectUpdated(const QRectF &rect);

public slots:
    void setSceneRect(const QRectF &rect);
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

private:
    void fitToView();

    Q3PlotScene *scene_;
    QColor backgroundColor_;
    Qt::AspectRatioMode aspectRatioMode_;
    int tickLength_;
    QRectF sceneRect_;
    QRectF unfitRect_;
};

#endif
