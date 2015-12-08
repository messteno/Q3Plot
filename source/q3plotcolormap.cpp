#include "q3plotcolormap.h"

Q3PlotColorMap::Q3PlotColorMap()
{

}

QColor Q3PlotColorMap::colorAt(qreal level)
{

    QColor color(255, 255, 255);
    qreal dr, dg, db;

    if (level < 0.1242)
    {
        db = 0.504 + ((1. - 0.504) / 0.1242) * level;
        dg = dr = 0.;
    }
    else if (level < 0.3747)
    {
        db = 1.;
        dr = 0.;
        dg = (level - 0.1242) * (1. / (0.3747 - 0.1242));
    }
    else if (level < 0.6253)
    {
        db = (0.6253 - level) * (1. / (0.6253 - 0.3747));
        dg = 1.;
        dr = (level - 0.3747) * (1. / (0.6253 - 0.3747));
    }
    else if (level < 0.8758)
    {
        db = 0.;
        dr = 1.;
        dg = (0.8758 - level) * (1. / (0.8758 - 0.6253));
    }
    else
    {
        db = 0.;
        dg = 0.;
        dr = 1. - (level - 0.8758) * ((1. - 0.504) / (1. - 0.8758));
    }

    color.setRed(dr * 255);
    color.setGreen(dg * 255);
    color.setBlue(db * 255);

    return color;
}

