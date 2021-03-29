#include "./include/discview.h"

DiscView::DiscView(QWidget *parent, QString discName, QString systemType, QString memory) :
    QWidget(parent),
    ui(new Ui::DiscView)
{
    ui->setupUi(this);
    ui->discName->setText(discName);
    ui->systemType->setText(systemType);
    ui->memory->setText(memory);
}

DiscView::~DiscView()
{
    delete ui;
}
