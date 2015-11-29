#ifndef Q3PLOTSCENE_H
#define Q3PLOTSCENE_H

#include <QRectF>
#include <QWidget>
#include <QObject>

#include "q3plotitem.h"

class Q3PlotScene : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QRectF sceneRect_ READ sceneRect WRITE setSceneRect)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    enum SceneSizeConstraints {
        OneToOneConstraints,
        ScaleToViewConstraints,
    };

    explicit Q3PlotScene(QObject *parent = 0);
    explicit Q3PlotScene(const QRectF &rect, QObject *parent = 0);

    QRectF sceneRect() const;
    void setSceneRect(const QRectF &rect);
    void fitToSize(const QSize &window,
                   SceneSizeConstraints constraints = ScaleToViewConstraints);

    void addItem(Q3PlotItem *item);
    void drawItems(QPainter &painter);
    void drawBackground(QPainter &painter, const QRectF &rect);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &brush);

signals:
    void sceneRectUpdated(const QRectF &rect);

public slots:

private:
    QRectF sceneRect_;
    QRectF unfitRect_; // stores origin scene rectangle before fitting
    bool hasSceneRect_;

    QList<Q3PlotItem *> items_;
    QColor backgroundColor_;
};

#endif // Q3PLOTSCENE_H
