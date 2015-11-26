#include <qmath.h>

#include "q3plotscene.h"

Q3PlotScene::Q3PlotScene(QObject *parent) :
    QObject(parent),
    hasSceneRect_(false)
{

}

Q3PlotScene::Q3PlotScene(const QRectF &rect, QObject *parent) :
    hasSceneRect_(false)
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
        sceneRect_ = rect;
    }
}

void Q3PlotScene::setSceneRect(const QRectF &rect, const QRect &window,
                               Q3PlotScene::SceneSizeConstraints constraints)
{
    if (constraints == OneToOneConstraints) {
        setSceneRect(rect);
        return;
    }

    qreal ratio = qMin(window.width() / rect.width(),
                       window.height() / rect.height());
    QPointF rectCenter = rect.center();
    QPointF fitInViewSize(window.width() / ratio, window.height() / ratio);
    QRectF fitInViewRect = QRectF(rectCenter - fitInViewSize / 2,
                                  rectCenter + fitInViewSize / 2);
    setSceneRect(fitInViewRect);
}

void Q3PlotScene::addItem(Q3PlotItem *item)
{
    items_.append(item);
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
