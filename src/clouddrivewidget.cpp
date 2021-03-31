#include "./include/clouddrivewidget.h"

CloudDriveWidget::CloudDriveWidget(QWidget *parent, QString name, QPixmap image, QString size) :
    QWidget(parent),
    ui(new Ui::CloudDriveWidget)
{
    ui->setupUi(this);
    ui->driveName->setText(name);
    ui->driveSize->setText(size);
    ui->driveLogo->setPixmap(image);
    connect(this, SIGNAL(clicked(QString)), parent, SLOT(open_cloud_drive(QString)));
}

CloudDriveWidget::~CloudDriveWidget()
{
    delete ui;
}

void CloudDriveWidget::mousePressEvent(QMouseEvent *event) {
    emit clicked(QDir::homePath() + "/" + ui->driveName->text());
}

void CloudDriveWidget::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
