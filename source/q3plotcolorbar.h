#ifndef Q3PLOTCOLORBAR_H
#define Q3PLOTCOLORBAR_H

#include "q3plotaxis.h"
#include "q3plotcolormap.h"

class Q3PlotColorBar : public Q3PlotAxis
{
    Q_OBJECT
public:
    explicit Q3PlotColorBar(Q3PlotFrame::LogicalPosition position, QWidget *parent = 0);
    virtual QSize sizeHint() const;

signals:

public slots:
    virtual void paintEvent(QPaintEvent *event);

private:
    int barWidth_;
    Q3PlotColorMap colorMap_;
};

#endif // Q3PLOTCOLORBAR_H
