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
