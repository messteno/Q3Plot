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
    backgroundBrush_(QColor(0x1a, 0x1a, 0x1a)),
    constraints_(Q3PlotScene::OneToOneConstraints)
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
   sceneRect.moveTop(sceneRect.top() + diff.y() / sy);

   scene_->setSceneRect(sceneRect);
   update();
}

void Q3PlotView::scaleViewport(const QPoint &pos, qreal scale)
{
    if (!scene_)
        return;

    QRectF sceneRect = scene_->sceneRect();
    if (sceneRect.isNull())
        return;

    QPointF scenePos = mapToScene(pos);

    QPointF topLeft = sceneRect.topLeft();
    QPointF bottomRight = sceneRect.bottomRight();
    sceneRect.setTopLeft(scenePos + scale * (topLeft - scenePos));
    sceneRect.setBottomRight(scenePos + scale * (bottomRight - scenePos));

    scene_->setSceneRect(sceneRect);
    update();
}

QPointF Q3PlotView::mapToScene(const QPoint &point)
{
    if (!scene_)
        return point;

    QRectF sceneRect = scene_->sceneRect();
    if (sceneRect.isNull())
        return point;

    qreal sceneX = sceneRect.left()
            + point.x() / (qreal) viewport_->width() * sceneRect.width();
    qreal sceneY = sceneRect.bottom()
            - point.y() / (qreal) viewport_->height() * sceneRect.height();

    qDebug() << sceneX << sceneY;

    return QPointF(sceneX, sceneY);
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

void Q3PlotView::setConstraints(Q3PlotScene::SceneSizeConstraints constraints)
{
    constraints_ = constraints;
    scene_->setSceneRect(scene_->sceneRect(), viewport_->window()->rect(),
                         constraints);
    update();
}

void Q3PlotView::setSceneRect(const QRectF &rect)
{
    scene_->setSceneRect(rect, viewport_->window()->rect(), constraints_);
    update();
}

void Q3PlotView::paintEvent(QPaintEvent *event)
{
}

void Q3PlotView::resizeEvent(QResizeEvent *event)
{

}
