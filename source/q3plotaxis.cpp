#include <QDebug>
#include <qmath.h>

#include "q3plotframe.h"
#include "q3plotaxis.h"

Q3PlotAxis::Q3PlotAxis(Q3PlotFrame::LogicalPosition position, QWidget *parent) :
    QWidget(parent),
    lower_(0),
    upper_(0),
    position_(position),
    autoTickCount_(7),
    tickStep_(1),
    locale_(QLocale::C),
    numberFormatChar_('g'),
    numberPrecision_(6),
    labelsVisible_(true)
{

}

void Q3PlotAxis::setRange(qreal lower, qreal upper)
{
    lower_ = lower;
    upper_ = upper;

    generateAutoTicks();
}

const QVector<qreal>& Q3PlotAxis::ticks() const
{
    return ticks_;
}

void Q3PlotAxis::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::white);

    QFontMetrics fm(font());
    QVector<int> tp = tickPositions();
    int margin = Q3PlotFrameContainer::Margin;

    switch (position_) {
    case Q3PlotFrame::PositionLeft:
        if (labelsVisible_) {
            for (int i = 0; i < ticks_.count(); ++i) {
                if (tp[i] + margin - fm.height() / 3. < 0
                        || tp[i] + margin + fm.height() / 3. > height()) {
                    continue;
                }
                painter.drawText(QPointF(width() - margin - fm.width(labels_[i]) - 1,
                                         tp[i] + margin + fm.height() / 3),
                                 labels_[i]);
            }
        }
        break;
    case Q3PlotFrame::PositionTop:
        if (labelsVisible_) {
            for (int i = 0; i < ticks_.count(); ++i) {
                if (tp[i] + margin - fm.width(labels_[i]) / 2 < 0
                        || tp[i] + margin + fm.width(labels_[i]) / 2 > width()) {
                    continue;
                }
                painter.drawText(QPointF(tp[i] + margin - fm.width(labels_[i]) / 2,
                                         height() - margin - 1), labels_[i]);
            }
        }
        break;
    case Q3PlotFrame::PositionRight:
        if (labelsVisible_) {
            for (int i = 0; i < ticks_.count(); ++i) {
                if (tp[i] + margin - fm.height() / 3. < 0
                        || tp[i] + margin + fm.height() / 3. > height()) {
                    continue;
                }
                painter.drawText(QPointF(margin, tp[i] + margin + fm.height() / 3),
                                 labels_[i]);
            }
        }
        break;
    case Q3PlotFrame::PositionBottom:
        if (labelsVisible_) {
            for (int i = 0; i < ticks_.count(); ++i) {
                if (tp[i] + margin - fm.width(labels_[i]) / 2 < 0
                        || tp[i] + margin + fm.width(labels_[i]) / 2 > width()) {
                    continue;
                }
                painter.drawText(QPointF(tp[i] + margin - fm.width(labels_[i]) / 2,
                                         margin + 2. / 3. * fm.height()), labels_[i]);
            }
        }
        break;
    }

    painter.end();
}

void Q3PlotAxis::rerange(const QRectF &rect)
{
    switch (position_) {
    case Q3PlotFrame::PositionLeft:
    case Q3PlotFrame::PositionRight:
        setRange(rect.top(), rect.bottom());
        break;
    case Q3PlotFrame::PositionBottom:
    case Q3PlotFrame::PositionTop:
        setRange(rect.left(), rect.right());
        break;
    }
}

int Q3PlotAxis::maxLabelWidth() const
{
    QFontMetrics fm(font());

    int maxlw = 0;
    for (int i = 0; i < labels_.count(); ++i) {
        int lw = fm.width(labels_[i]);
        if (maxlw < lw)
            maxlw = lw;
    }

    return maxlw;
}

void Q3PlotAxis::setLabelsVisible(bool labelsVisible)
{
    labelsVisible_ = labelsVisible;
}

QSize Q3PlotAxis::sizeHint() const
{
    int margin = Q3PlotFrameContainer::Margin;

    switch (position_) {
        case Q3PlotFrame::PositionLeft:
        case Q3PlotFrame::PositionRight: {
            if (!labelsVisible_)
                return QSize(2 * margin, QWIDGETSIZE_MAX);

            int axisWidth = maxLabelWidth() + 2 * margin;
            axisWidth = axisWidth < 50 ? 50 : axisWidth;
            return QSize(axisWidth, QWIDGETSIZE_MAX);
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

const QVector<int> Q3PlotAxis::tickPositions() const
{
    QVector<int> tickPositions(ticks_.count());
    for (int i = 0; i < ticks_.count(); ++i) {
        tickPositions[i] = coordinateToPixel(ticks_[i]);
    }
    return tickPositions;
}

void Q3PlotAxis::generateAutoTicks()
{
    ticks_.clear();

    tickStep_ = (upper_ - lower_) / (double) (autoTickCount_ + 1e-10);
    qreal magnitudeFactor = qPow(10., qFloor(qLn(tickStep_) / qLn(10.)));
    qreal tickStepMantissa = tickStep_ / magnitudeFactor;
    if (tickStepMantissa < 5) {
        tickStep_ = (int) (tickStepMantissa * 2.) / 2. * magnitudeFactor;
    } else {
        tickStep_ = (int) (tickStepMantissa / 2.) * 2. * magnitudeFactor;
    }

    qint64 firstStep = floor(lower_ / tickStep_);
    qint64 lastStep = ceil(upper_ / tickStep_);

    int tickCount = lastStep - firstStep + 1;

    if (tickCount < 0)
        tickCount = 0;

    ticks_.resize(tickCount);
    labels_.resize(tickCount);

    for (int i = 0; i < tickCount; ++i) {
        ticks_[i] = (firstStep + i) * tickStep_;
        labels_[i] = locale_.toString(ticks_[i], numberFormatChar_.toLatin1(),
                                      numberPrecision_);
    }
}

int Q3PlotAxis::coordinateToPixel(qreal coordinate) const
{
    int size = 0;
    int margin = Q3PlotFrameContainer::Margin;

    switch (position_) {
    case Q3PlotFrame::PositionLeft:
    case Q3PlotFrame::PositionRight:
        size = height() - 2 * margin - 1;
        return size - (coordinate - lower_) / (upper_ - lower_) * size;
    case Q3PlotFrame::PositionBottom:
    case Q3PlotFrame::PositionTop:
        size = width() - 2 * margin - 1;
        return (coordinate - lower_) / (upper_ - lower_) * size;
    }
}
