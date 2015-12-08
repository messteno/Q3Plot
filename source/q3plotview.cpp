#include <QPainter>
#include <QDebug>
#include <QGraphicsView>
#include <QLineF>
#include <QEvent>
#include <QVBoxLayout>
#include <QStyleOption>

#include "q3plotaxis.h"
#include "q3plotcolorbar.h"
#include "q3plotview.h"

Q3PlotView::Q3PlotView(Q3PlotScene *scene, QWidget *parent) :
    Q3PlotFrame(parent),
    scene_(scene),
    backgroundColor_(0x2a, 0x2a, 0x2a),
    aspectRatioMode_(Qt::IgnoreAspectRatio),
    tickLength_(5)
{
    setSceneRect(scene_->sceneRect());
    connect(scene, SIGNAL(sceneRectUpdated(QRectF)),
            this, SLOT(setSceneRect(QRectF)));
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
    if (scene_) {
        painter.save();
        if (!sceneRect_.isNull())
        {
            painter.translate(-0.5, -0.5);
            qreal sx = painter.window().width() / sceneRect_.width();
            qreal sy = painter.window().height() / sceneRect_.height();
            painter.scale(sx, -sy);
            painter.translate(-sceneRect_.left(), -sceneRect_.bottom());
        }
        else
            ; // TODO: calc sceneRect
        scene_->drawItems(painter);
        painter.restore();
    }
}

void Q3PlotView::moveViewport(const QPoint &diff)
{
   if (!scene_)
       return;

   QRectF sceneRect = sceneRect_;
   if (sceneRect.isNull())
       return;

   // TODO: maybe wrap to a function
   qreal sx = viewport_->width() / sceneRect.width();
   qreal sy = viewport_->height() / sceneRect.height();
   sceneRect.moveLeft(sceneRect.left() - diff.x() / sx);
   sceneRect.moveTop(sceneRect.top() + diff.y() / sy);

   setSceneRect(sceneRect);
   update();
}

void Q3PlotView::scaleViewport(const QPoint &pos, qreal scale)
{
    if (!scene_)
        return;

    if (sceneRect_.isNull())
        return;

    QPointF scenePos = mapToScene(pos);

    QPointF topLeft = sceneRect_.topLeft();
    QPointF bottomRight = sceneRect_.bottomRight();
    sceneRect_.setTopLeft(scenePos + scale * (topLeft - scenePos));
    sceneRect_.setBottomRight(scenePos + scale * (bottomRight - scenePos));

    setSceneRect(sceneRect_);
    update();
}

QPointF Q3PlotView::mapToScene(const QPoint &point)
{
    if (!scene_)
        return point;

    if (sceneRect_.isNull())
        return point;

    qreal sceneX = sceneRect_.left()
            + point.x() / (qreal) viewport_->width() * sceneRect_.width();
    qreal sceneY = sceneRect_.bottom()
            - point.y() / (qreal) viewport_->height() * sceneRect_.height();

    return QPointF(sceneX, sceneY);
}

QPoint Q3PlotView::mapFromScene(const QPointF &point)
{
    if (!scene_)
        return QPoint();

    if (sceneRect_.isNull())
        return QPoint();

    int viewportX = (point.x() - sceneRect_.topLeft().x()) / sceneRect_.width()
            * (viewport_->width() - 1);
    int viewportY = viewport_->height() - 1
            - (point.y() - sceneRect_.topLeft().y())
            / sceneRect_.height() * (viewport_->height() - 1);
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

void Q3PlotView::setAspectRatioMode(Qt::AspectRatioMode aspectRatioMode)
{
    aspectRatioMode_ = aspectRatioMode;
    layoutAndFit();
    update();
}

void Q3PlotView::setSceneRect(const QRectF &rect)
{
    sceneRect_ = rect;
    unfitRect_ = rect;
    emit sceneRectUpdated(sceneRect_);

    layoutAndFit();
    update();
}

void Q3PlotView::layoutAndFit()
{
    layoutChildren();

    if (aspectRatioMode_ == Qt::IgnoreAspectRatio) {
        return;
    }

    QSize prevViewportSize;

    fitToView();

    int iteration = 0;
    do
    {
        prevViewportSize = viewport_->size();
        layoutChildren();
        fitToView();
        iteration++;
    } while ((viewport_->size().height() > prevViewportSize.height()
              || viewport_->size().width() > prevViewportSize.width())
             && (iteration < 3));
}

void Q3PlotView::fitToView()
{
    if (aspectRatioMode_ == Qt::IgnoreAspectRatio) {
        return;
    }

    QRectF rect = unfitRect_;
    qreal ratio = qMin(viewport_->width() / rect.width(),
                       viewport_->height() / rect.height());
    QPointF rectCenter = rect.center();
    QPointF fitInViewSize(viewport_->width() / ratio, viewport_->height() / ratio);
    sceneRect_ = QRectF(rectCenter - fitInViewSize / 2,
                        rectCenter + fitInViewSize / 2);
    emit sceneRectUpdated(sceneRect_);
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

    axis->rerange(sceneRect_);
    connect(this, SIGNAL(sceneRectUpdated(QRectF)), axis, SLOT(rerange(QRectF)));
    container->prependWidget(axis);

    layoutAndFit();
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

Q3PlotColorBar* Q3PlotView::addColorBar(Q3PlotFrame::LogicalPosition colorBarPosition,
                                        qreal lower, qreal upper)
{
    Q3PlotFrameContainer *container = frameContainers_[colorBarPosition];
    Q3PlotColorBar *colorBar = new Q3PlotColorBar(colorBarPosition, container);

    colorBar->setRange(lower, upper);
    container->appendWidget(colorBar);

    layoutAndFit();
    update();

    return colorBar;
}

void Q3PlotView::paintEvent(QPaintEvent *event)
{
}

void Q3PlotView::resizeEvent(QResizeEvent *event)
{
    layoutAndFit();
}
