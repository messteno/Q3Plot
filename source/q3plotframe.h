#ifndef Q3PLOTFRAME_H
#define Q3PLOTFRAME_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QMap>
#include <QBoxLayout>
#include <QWidgetList>

#include "q3plotviewport.h"

class Q3PlotFrameContainer;
class Q3PlotAxis;

class Q3PlotFrame : public QWidget
{
    Q_OBJECT
public:
    enum LogicalPosition {
        PositionLeft = 0,
        PositionTop = 1,
        PositionRight = 2,
        PositionBottom = 3,
    };

    explicit Q3PlotFrame(QWidget *parent = 0);
    virtual ~Q3PlotFrame();

    Q3PlotViewport *viewport() const;
    virtual void drawViewport(QPainter &painter);
    virtual void moveViewport(const QPoint &diff);
    virtual void scaleViewport(const QPoint &pos, qreal scale);
    void layoutChildren();

signals:

public slots:

protected:
    Q3PlotViewport *viewport_;
    QMap<LogicalPosition, Q3PlotFrameContainer*> frameContainers_;
};

class Q3PlotFrameContainer : public QWidget
{
    Q_OBJECT
public:
    Q3PlotFrameContainer(Q3PlotFrame::LogicalPosition position, QWidget *parent = 0);
    void prependWidget(QWidget *widget);
    void appendWidget(QWidget *widget);

    QWidgetList widgets() const;

    Q3PlotAxis* axis() const;
    bool hasAxis() const;

    QSize sizeHint() const;

    static const int Margin = 6;

private:
    QBoxLayout *layout_;
    Q3PlotFrame::LogicalPosition position_;
};

#endif // Q3PLOTFRAME_H
