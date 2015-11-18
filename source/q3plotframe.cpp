#include <QDebug>
#include "q3plotframe.h"

Q3PlotFrame::Q3PlotFrame(QWidget *parent) :
    QWidget(parent),
    viewport_(new Q3PlotViewport(*this))
{
    layoutChildren();
//    viewport_->setCursor(Qt::OpenHandCursor);
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

void Q3PlotFrame::layoutChildren()
{
    viewport_->setGeometry(rect());
    viewport_->show();
}

bool Q3PlotFrame::event(QEvent *event)
{
    switch(event->type()) {
    case QEvent::Resize:
        layoutChildren();
    }
}
