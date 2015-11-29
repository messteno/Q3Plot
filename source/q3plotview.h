#ifndef Q3PLOTVIEW_H
#define Q3PLOTVIEW_H

#include <QWidget>
#include <iostream>

#include "q3plotscene.h"
#include "q3plotframe.h"
#include "q3plotaxis.h"

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

    void setConstraints(Q3PlotScene::SceneSizeConstraints constraints);
    void setSceneRect(const QRectF &rect);

    virtual QSize sizeHint() const;

    Q3PlotAxis* axis(Q3PlotFrame::LogicalPosition axisPosition);
    Q3PlotAxis *addAxis(Q3PlotFrame::LogicalPosition axisPosition);
    bool hasAxis(Q3PlotFrame::LogicalPosition axisPosition);
//    void removeAxis(Q3PlotFrame::LogicalPosition axisPosition);

signals:
public slots:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

private:
    Q3PlotScene *scene_;
    QColor backgroundColor_;
    Q3PlotScene::SceneSizeConstraints constraints_;
    int tickLength_;
};

#endif
