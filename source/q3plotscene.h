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

public:
    enum SceneSizeConstraints {
        OneToOneConstraints,
        FitInViewConstraints,
    };

    explicit Q3PlotScene(QObject *parent = 0);
    explicit Q3PlotScene(const QRectF &rect, QObject *parent = 0);

    QRectF sceneRect() const;
    void setSceneRect(const QRectF &rect);
    void setSceneRect(const QRectF &rect, const QRect &window,
                      SceneSizeConstraints constraints = FitInViewConstraints);

    void addItem(Q3PlotItem *item);
    void drawItems(QPainter &painter);

signals:

public slots:

private:
    QRectF sceneRect_;
    bool hasSceneRect_;

    QList<Q3PlotItem *> items_;
};

#endif // Q3PLOTSCENE_H
