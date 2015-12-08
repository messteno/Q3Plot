#include <QImage>

#include "q3plotcolorbar.h"

Q3PlotColorBar::Q3PlotColorBar(Q3PlotFrame::LogicalPosition position, QWidget *parent) :
    Q3PlotAxis(position, parent),
    barWidth_(20)
{

}

QSize Q3PlotColorBar::sizeHint() const
{
    int margin = Q3PlotFrameContainer::Margin;

    switch (position_) {
        case Q3PlotFrame::PositionLeft:
        case Q3PlotFrame::PositionRight: {
            if (!labelsVisible_)
                return QSize(2 * margin + barWidth_, QWIDGETSIZE_MAX);

            int labelsWidth = maxLabelWidth() + 2 * margin;
            labelsWidth = labelsWidth < 50 ? 50 : labelsWidth;
            return QSize(labelsWidth + barWidth_, QWIDGETSIZE_MAX);
        }
        case Q3PlotFrame::PositionBottom:
        case Q3PlotFrame::PositionTop: {
            QFontMetrics fm(font());
            if (!labelsVisible_)
                return QSize(QWIDGETSIZE_MAX, 2 * margin);

            return QSize(QWIDGETSIZE_MAX, 2 * margin + fm.height());
        }
    }
    return QSize(0, 0);
}

void Q3PlotColorBar::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    int margin = Q3PlotFrameContainer::Margin;
    QImage img(barWidth_, height() - 2 * margin, QImage::Format_RGB888);

    for (int i = 0; i < img.height(); ++i) {
        for (int j = 0; j < barWidth_; ++j) {
            qreal level = (qreal) (img.height() - i) / img.height();
            img.setPixel(j, i, colorMap_.colorAt(level).rgb());
        }
    }
    painter.drawImage(0, margin, img);

    painter.end();

    Q3PlotAxis::paintEvent(event);
}
