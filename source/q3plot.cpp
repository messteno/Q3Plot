#include <QMenuBar>
#include <QFileDialog>

#include "q3plot.h"
#include "ui_q3plot.h"

Q3Plot::Q3Plot(Q3PlotView *view, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Q3Plot),
    view_(view)
{
    init();
}

Q3Plot::Q3Plot(Q3PlotScene *scene, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Q3Plot),
    view_(new Q3PlotView(scene, this))
{
    init();
}

Q3Plot::~Q3Plot()
{
    delete ui;
}

void Q3Plot::init()
{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(view_);
    view_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(0x2a, 0x2a, 0x2a));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void Q3Plot::on_setOneToOneConstraintsButton_clicked()
{
    view_->setAspectRatioMode(Qt::KeepAspectRatio);
}

void Q3Plot::on_printScreenButton_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    QString path = fileDialog->getSaveFileName(this, tr("Save as image"),
                                               "../data",
                                               tr("PNG file (*.png)"));

    if (path.isEmpty())
        return;

    QFileInfo file(path);
    if (file.suffix().isEmpty())
        path += ".png";

    QImage img(view_->size(), QImage::Format_ARGB32);
    QPainter painter(&img);
    view_->render(&painter);

    img.save(path);
}
