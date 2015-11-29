#include <qmath.h>
#include <QDebug>
#include <QPalette>

#include "q3plotscene.h"

Q3PlotScene::Q3PlotScene(QObject *parent) :
    QObject(parent),
    hasSceneRect_(false),
    backgroundColor_(0x1a, 0x1a, 0x1a)
{

}

Q3PlotScene::Q3PlotScene(const QRectF &rect, QObject *parent) :
    hasSceneRect_(false),
    backgroundColor_(QColor(0x1a, 0x1a, 0x1a))
{
    setSceneRect(rect);
}

QRectF Q3PlotScene::sceneRect() const
{
    return sceneRect_;
}

void Q3PlotScene::setSceneRect(const QRectF &rect)
{
    if (rect != sceneRect_) {
        hasSceneRect_ = !rect.isNull();
        unfitRect_ = rect;
        sceneRect_ = rect;
        emit sceneRectUpdated(sceneRect_);
    }
}

void Q3PlotScene::fitToSize(const QSize &window,
                            Q3PlotScene::SceneSizeConstraints constraints)
{
    if (!hasSceneRect_ || constraints == ScaleToViewConstraints) {
        return;
    }

    QRectF rect = unfitRect_;
    qreal ratio = qMin(window.width() / rect.width(),
                       window.height() / rect.height());
    QPointF rectCenter = rect.center();
    QPointF fitInViewSize(window.width() / ratio, window.height() / ratio);
    sceneRect_ = QRectF(rectCenter - fitInViewSize / 2,
                        rectCenter + fitInViewSize / 2);
    emit sceneRectUpdated(sceneRect_);
}

void Q3PlotScene::addItem(Q3PlotItem *item)
{
    items_.append(item);
}

void Q3PlotScene::drawBackground(QPainter &painter, const QRectF &rect)
{
    painter.fillRect(rect, backgroundColor_);
}

void Q3PlotScene::drawItems(QPainter &painter)
{
    painter.save();

    QPen pen(Qt::white);
    pen.setWidth(1);
    pen.setCosmetic(true);
    painter.setPen(pen);

    painter.setBrush(QColor(0x53, 0x97, 0x32));

    if (hasSceneRect_)
    {
        qreal sx = painter.window().width() / sceneRect_.width();
        qreal sy = painter.window().height() / sceneRect_.height();
        painter.scale(sx, -sy);
        painter.translate(-sceneRect_.left(), -sceneRect_.bottom());
    }
    else
        ; // TODO: calc sceneRect

    foreach(Q3PlotItem *item, items_)
        item->draw(painter);

    painter.restore();
}

QColor Q3PlotScene::backgroundColor() const
{
    return backgroundColor_;
}

void Q3PlotScene::setBackgroundColor(const QColor &color)
{
    backgroundColor_ = color;
}
