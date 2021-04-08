#include "./include/discview.h"

DiscView::DiscView(QWidget *parent, QString discName, QString systemType, QString currentMemory, QString currentMetrics, QString totalMemory, QString totalMetrics, QString ready, QString readOnly) :
    QWidget(parent),
    ui(new Ui::DiscView)
{
    ui->setupUi(this);
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);
    ui->discName->setText(discName);
    ui->systemType->setText(systemType);
    ui->currentMemory->setText(currentMemory);
    ui->currentMetrics->setText(currentMetrics);
    ui->totalMemory->setText(totalMemory);
    ui->totalMetrics->setText(totalMetrics);
    ui->isReadOnly->setText(readOnly);
    ui->isReady->setText(ready);
}

DiscView::~DiscView()
{
    delete ui;
}
