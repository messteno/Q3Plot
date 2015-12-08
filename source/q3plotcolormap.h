#ifndef Q3PLOTCOLORMAP_H
#define Q3PLOTCOLORMAP_H

#include <QColor>

class Q3PlotColorMap
{
public:
    Q3PlotColorMap();
    QColor colorAt(qreal level);
};

#endif // Q3PLOTCOLORMAP_H
