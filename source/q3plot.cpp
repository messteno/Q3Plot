#include <QMenuBar>

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
