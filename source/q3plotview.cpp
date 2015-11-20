#include <QPainter>
#include <QDebug>
#include <QGraphicsView>
#include <QLineF>
#include <QEvent>
#include <QVBoxLayout>
#include <QStyleOption>

#include "q3plotview.h"

Q3PlotView::Q3PlotView(Q3PlotScene *scene, QWidget *parent) :
    Q3PlotFrame(parent),
    scene_(scene),
    backgroundBrush_(QColor(0x1a, 0x1a, 0x1a))
{
}

Q3PlotView::~Q3PlotView()
{
}

void Q3PlotView::drawBackground(QPainter &painter, const QRectF &rect)
{
    if (scene_ && backgroundBrush_.style() == Qt::NoBrush) {
        return;
    }

    painter.fillRect(rect, backgroundBrush_);
}

void Q3PlotView::drawViewport(QPainter &painter)
{
    QPixmap backgroundPixmap(viewport()->size());
    QPainter backgroundPainter(&backgroundPixmap);

    drawBackground(backgroundPainter, window()->rect());
    painter.drawPixmap(QPoint(), backgroundPixmap);

    painter.setRenderHint(QPainter::Antialiasing);

    if (scene_)
        scene_->drawItems(painter);
}

void Q3PlotView::moveViewport(const QPoint &diff)
{
   if (!scene_)
       return;

   QRectF sceneRect = scene_->sceneRect();
   if (sceneRect.isNull())
       return;

   // TODO: maybe wrap to a function
   qreal sx = viewport_->width() / sceneRect.width();
   qreal sy = viewport_->height() / sceneRect.height();
   sceneRect.moveLeft(sceneRect.left() - diff.x() / sx);
   sceneRect.moveTop(sceneRect.top() - diff.y() / sy);

   scene_->setSceneRect(sceneRect);
   update();
}

QBrush Q3PlotView::backgroundBrush() const
{
    return backgroundBrush_;
}

void Q3PlotView::setBackgroundBrush(const QBrush &brush)
{
    backgroundBrush_ = brush;
    update();
}

void Q3PlotView::paintEvent(QPaintEvent *event)
{
}
