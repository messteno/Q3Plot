#ifndef Q3PLOTSCENE_H
#define Q3PLOTSCENE_H

#include <QRectF>
#include <QObject>

class Q3PlotScene : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QRectF sceneRect_ READ sceneRect WRITE setSceneRect)

public:
    explicit Q3PlotScene(QObject *parent = 0);
    explicit Q3PlotScene(const QRectF &rect, QObject *parent = 0);

    QRectF sceneRect() const;
    void setSceneRect(const QRectF &rect);

signals:

public slots:

private:
    QRectF sceneRect_;
    bool hasSceneRect_;
};

#endif // Q3PLOTSCENE_H
