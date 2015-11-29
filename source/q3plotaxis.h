#ifndef Q3PLOTAXIS_H
#define Q3PLOTAXIS_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QLocale>

#include "q3plotframe.h"

class Q3PlotAxis : public QWidget
{
    Q_OBJECT
public:
    explicit Q3PlotAxis(Q3PlotFrame::LogicalPosition, QWidget *parent = 0);
    void setRange(qreal lower, qreal upper);
    const QVector<qreal> &ticks() const;
    const QVector<int> tickPositions() const;
    int maxLabelWidth() const;
    void setLabelsVisible(bool labelsVisible);
    QSize sizeHint() const;

signals:

public slots:
    virtual void paintEvent(QPaintEvent *event);
    void rerange(const QRectF &rect);

private:
    void generateAutoTicks();
    int coordinateToPixel(qreal coordinate) const;

    qreal lower_;
    qreal upper_;
    QVector<qreal> ticks_;
    QVector<QString> labels_;
    Q3PlotFrame::LogicalPosition position_;
    int autoTickCount_;
    qreal tickStep_;
    QLocale locale_;
    QLatin1Char numberFormatChar_;
    int numberPrecision_;
    bool labelsVisible_;
};

#endif // Q3PLOTAXIS_H
