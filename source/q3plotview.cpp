#include <QPainter>
#include <QDebug>
#include <QGraphicsView>
#include <QLineF>
#include <QEvent>
#include <QVBoxLayout>
#include <QStyleOption>

#include "q3plotaxis.h"
#include "q3plotview.h"

Q3PlotView::Q3PlotView(Q3PlotScene *scene, QWidget *parent) :
    Q3PlotFrame(parent),
    scene_(scene),
    backgroundColor_(0x2a, 0x2a, 0x2a),
    constraints_(Q3PlotScene::OneToOneConstraints),
    tickLength_(5)
{
    setBackgroundColor(backgroundColor_);
}

Q3PlotView::~Q3PlotView()
{
}

void Q3PlotView::drawViewport(QPainter &painter)
{
    if (scene_)
        scene_->drawBackground(painter, viewport_->rect());

    Q3PlotAxis *xAxis = axis(PositionBottom);
    if (!xAxis)
        xAxis = axis(PositionTop);

    QVector<int> xtp;
    if (xAxis) {
        xtp = xAxis->tickPositions();

        painter.setPen(QPen(QColor(0x30, 0x40, 0x30), 1, Qt::DashLine));
        for (int i = 0; i < xtp.count(); ++i) {
            painter.drawLine(xtp.at(i), 0, xtp.at(i), viewport_->height() - 1);
        }
    }

    Q3PlotAxis *yAxis = axis(PositionLeft);
    if (!yAxis)
        yAxis = axis(PositionRight);

    QVector<int> ytp;
    if (yAxis) {
        ytp = yAxis->tickPositions();

        painter.setPen(QPen(QColor(0x30, 0x40, 0x30), 1, Qt::DashLine));
        for (int i = 0; i < ytp.count(); ++i) {
            painter.drawLine(0, ytp.at(i),
                             viewport_->width() - 1, ytp.at(i));
        }
    }

    QPoint xoy = mapFromScene(QPointF(0, 0));
    painter.setPen(QColor(0xa0, 0xa0, 0xa0));
    painter.drawLine(0, xoy.y(), viewport_->width() - 1, xoy.y());
    painter.drawLine(xoy.x(), 0, xoy.x(), viewport_->height() - 1);

    painter.setPen(Qt::white);
    painter.setBrush(Qt::transparent);
    painter.drawRect(0, 0, viewport_->width() - 1, viewport_->height() - 1);

    painter.setPen(Qt::white);
    if (hasAxis(PositionTop)) {
        for (int i = 0; i < xtp.count(); ++i) {
            painter.drawLine(xtp.at(i), 0, xtp.at(i), tickLength_);
        }
    }
    if (hasAxis(PositionBottom)) {
        for (int i = 0; i < xtp.count(); ++i) {
            painter.drawLine(xtp.at(i), viewport_->height() - tickLength_ - 1,
                             xtp.at(i), viewport_->height() - 1);
        }
    }
    if (hasAxis(PositionLeft)) {
        for (int i = 0; i < ytp.count(); ++i) {
            painter.drawLine(0, ytp.at(i),
                             tickLength_, ytp.at(i));
        }
    }
    if (hasAxis(PositionRight)) {
        for (int i = 0; i < ytp.count(); ++i) {
            painter.drawLine(viewport_->width() - tickLength_ - 1, ytp.at(i),
                             viewport_->width() - 1, ytp.at(i));
        }
    }

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
    layoutChildren();
    scene_->fitToSize(viewport_->size(), constraints_);
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

    return QPointF(sceneX, sceneY);
}

QPoint Q3PlotView::mapFromScene(const QPointF &point)
{
    if (!scene_)
        return QPoint();

    QRectF sceneRect = scene_->sceneRect();
    if (sceneRect.isNull())
        return QPoint();

    int viewportX = (point.x() - sceneRect.topLeft().x()) / sceneRect.width()
            * (viewport_->width() - 1);
    int viewportY = viewport_->height() - 1
            - (point.y() - sceneRect.topLeft().y())
            / sceneRect.height() * (viewport_->height() - 1);
    return QPoint(viewportX, viewportY);

}

QColor Q3PlotView::backgroundColor() const
{
    return backgroundColor_;
}

void Q3PlotView::setBackgroundColor(const QColor &color)
{
    backgroundColor_ = color;

    QPalette pal(palette());
    pal.setColor(QPalette::Background, backgroundColor_);
    setAutoFillBackground(true);
    setPalette(pal);

    update();
}

int Q3PlotView::tickLength() const
{
    return tickLength_;
}

void Q3PlotView::setTickLength(int tickLength)
{
    tickLength_ = tickLength;
}

void Q3PlotView::setConstraints(Q3PlotScene::SceneSizeConstraints constraints)
{
    constraints_ = constraints;
    scene_->fitToSize(viewport_->size(), constraints_);
    update();
}

void Q3PlotView::setSceneRect(const QRectF &rect)
{
    scene_->setSceneRect(rect);
    scene_->fitToSize(viewport_->size(), constraints_);
    update();
}

QSize Q3PlotView::sizeHint() const
{
   return QSize(800, 600);
}

Q3PlotAxis* Q3PlotView::addAxis(Q3PlotFrame::LogicalPosition axisPosition)
{
    Q3PlotAxis *currentAxis = axis(axisPosition);
    if (currentAxis)
        return currentAxis;

    Q3PlotFrameContainer *container = frameContainers_[axisPosition];
    Q3PlotAxis *axis = new Q3PlotAxis(axisPosition, container);

    axis->rerange(scene_->sceneRect());
    connect(scene_, SIGNAL(sceneRectUpdated(QRectF)),
            axis, SLOT(rerange(QRectF)));
    container->prependWidget(axis);

    layoutChildren();
    scene_->fitToSize(viewport_->size(), constraints_);
    update();

    return axis;
}

bool Q3PlotView::hasAxis(Q3PlotFrame::LogicalPosition axisPosition)
{
    Q3PlotFrameContainer *container = frameContainers_[axisPosition];
    return container->hasAxis();
}

Q3PlotAxis* Q3PlotView::axis(Q3PlotFrame::LogicalPosition axisPosition)
{
    Q3PlotFrameContainer *container = frameContainers_[axisPosition];
    return container->axis();
}

void Q3PlotView::paintEvent(QPaintEvent *event)
{
}

void Q3PlotView::resizeEvent(QResizeEvent *event)
{
    layoutChildren();
    scene_->fitToSize(viewport_->size(), constraints_);
}
