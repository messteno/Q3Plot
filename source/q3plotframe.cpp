#include <QDebug>

#include "q3plotaxis.h"
#include "q3plotframe.h"

Q3PlotFrame::Q3PlotFrame(QWidget *parent) :
    QWidget(parent),
    viewport_(new Q3PlotViewport(*this))
{
    frameContainers_[PositionLeft] = new Q3PlotFrameContainer(PositionLeft, this);
    frameContainers_[PositionTop] = new Q3PlotFrameContainer(PositionTop, this);
    frameContainers_[PositionRight] = new Q3PlotFrameContainer(PositionRight, this);
    frameContainers_[PositionBottom] = new Q3PlotFrameContainer(PositionBottom, this);
    layoutChildren();
}

Q3PlotFrame::~Q3PlotFrame()
{

}

Q3PlotViewport *Q3PlotFrame::viewport() const
{
    return viewport_;
}

void Q3PlotFrame::drawViewport(QPainter &painter)
{
    Q_UNUSED(painter);
}

void Q3PlotFrame::moveViewport(const QPoint &diff)
{
    Q_UNUSED(diff);
}

void Q3PlotFrame::scaleViewport(const QPoint &pos, qreal scale)
{
    Q_UNUSED(pos);
    Q_UNUSED(scale);
}

void Q3PlotFrame::layoutChildren()
{
    const QRectF &widgetRect = rect();

    Q3PlotFrameContainer *lc = frameContainers_[PositionLeft];
    Q3PlotFrameContainer *tc = frameContainers_[PositionTop];
    Q3PlotFrameContainer *rc = frameContainers_[PositionRight];
    Q3PlotFrameContainer *bc = frameContainers_[PositionBottom];

    QPoint cornerBottomLeft = QPoint(lc->sizeHint().width(),
                                     widgetRect.height() - bc->sizeHint().height());
    QPoint cornerTopLeft = QPoint(lc->sizeHint().width(),
                                  tc->sizeHint().height());
    QPoint cornerBottomRight = QPoint(widgetRect.width() - rc->sizeHint().width() - 1,
                                      widgetRect.height() - bc->sizeHint().height());
    QPoint cornerTopRight = QPoint(widgetRect.width() - rc->sizeHint().width() - 1,
                                   tc->sizeHint().height());

    int margin = Q3PlotFrameContainer::Margin;
    lc->setGeometry(QRect(QPoint(0, cornerTopLeft.y() - margin),
                          QSize(lc->sizeHint().width() + 1,
                                cornerBottomLeft.y() - cornerTopLeft.y() + 2 * margin + 1)));
    tc->setGeometry(QRect(QPoint(cornerTopLeft.x() - margin, 0),
                          QSize(cornerTopRight.x() - cornerTopLeft.x() + 2 * margin + 1,
                                tc->sizeHint().height() + 1)));
    rc->setGeometry(QRect(QPoint(cornerTopRight.x(), cornerTopRight.y() - margin),
                          QSize(rc->sizeHint().width() + 1,
                                cornerBottomRight.y() - cornerTopRight.y() + 2 * margin + 1)));
    bc->setGeometry(QRect(QPoint(cornerBottomLeft.x() - margin, cornerBottomLeft.y()),
                          QSize(cornerBottomRight.x() - cornerBottomLeft.x() + 2 * margin + 1,
                                bc->sizeHint().height() + 1)));

    viewport_->setGeometry(QRect(cornerTopLeft, cornerBottomRight));
}

Q3PlotFrameContainer::Q3PlotFrameContainer(Q3PlotFrame::LogicalPosition position,
                                           QWidget *parent) :
    QWidget(parent),
    layout_(NULL),
    position_(position)
{
    switch (position_) {
    case Q3PlotFrame::PositionLeft:
        layout_ = new QBoxLayout(QBoxLayout::RightToLeft);
        break;
    case Q3PlotFrame::PositionTop:
        layout_ = new QBoxLayout(QBoxLayout::BottomToTop);
        break;
    case Q3PlotFrame::PositionRight:
        layout_ = new QBoxLayout(QBoxLayout::LeftToRight);
        break;
    case Q3PlotFrame::PositionBottom:
        layout_ = new QBoxLayout(QBoxLayout::TopToBottom);
        break;
    }
    setLayout(layout_);
    layout_->setMargin(0);
    layout_->setSpacing(0);
}

void Q3PlotFrameContainer::prependWidget(QWidget *widget)
{
    layout_->insertWidget(0, widget);
}

void Q3PlotFrameContainer::appendWidget(QWidget *widget)
{
    layout_->insertWidget(layout_->count(), widget);
}

QWidgetList Q3PlotFrameContainer::widgets() const
{
    QWidgetList list;
    const int layoutItemCount = layout_->count();
    for (int i = 0; i < layoutItemCount; ++i) {
        list.append(layout_->itemAt(i)->widget());
    }
    return list;
}

Q3PlotAxis *Q3PlotFrameContainer::axis() const
{
    const int layoutItemCount = layout_->count();
    for (int i = 0; i < layoutItemCount; ++i) {
        QWidget *widget = layout_->itemAt(i)->widget();
        Q3PlotAxis *axis = qobject_cast<Q3PlotAxis *>(widget);
        if (axis)
            return axis;
    }
    return NULL;
}

bool Q3PlotFrameContainer::hasAxis() const
{
    const int layoutItemCount = layout_->count();
    for (int i = 0; i < layoutItemCount; ++i) {
        if (qobject_cast<Q3PlotAxis *>(layout_->itemAt(i)->widget())) {
            return true;
        }
    }
    return false;
}

QSize Q3PlotFrameContainer::sizeHint() const
{
    QSize hint(0, 0);

    const int layoutItemCount = layout_->count();
    for (int i = 0; i < layoutItemCount; ++i) {
        QSize size = layout_->itemAt(i)->widget()->sizeHint();
        switch (position_) {
        case Q3PlotFrame::PositionLeft:
        case Q3PlotFrame::PositionRight:
            hint.setWidth(hint.width() + size.width());
            break;
        case Q3PlotFrame::PositionTop:
        case Q3PlotFrame::PositionBottom:
            hint.setHeight(hint.height() + size.height());
            break;
        }
    }

    if (hint.height() == 0)
        hint.setHeight(2 * Margin);
    if (hint.width() == 0)
        hint.setWidth(2 * Margin);

    return hint;
}
