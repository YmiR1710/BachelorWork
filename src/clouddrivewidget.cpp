#include "./include/clouddrivewidget.h"

CloudDriveWidget::CloudDriveWidget(QWidget *parent, QString name, QPixmap image, QString size) :
    QWidget(parent),
    ui(new Ui::CloudDriveWidget)
{
    ui->setupUi(this);
    defaultMode = true;
    ui->docsLogo->setVisible(false);
    ui->docsInfo->setVisible(false);
    ui->photoLogo->setVisible(false);
    ui->photoInfo->setVisible(false);
    ui->musicLogo->setVisible(false);
    ui->musicInfo->setVisible(false);
    ui->otherLogo->setVisible(false);
    ui->otherInfo->setVisible(false);
    ui->driveName->setText(name);
    ui->userName->setText(QDir::home().dirName());
    ui->driveSize->setText(size);
    ui->driveLogo->setPixmap(image);
    connect(this, SIGNAL(clicked(QString)), parent, SLOT(open_cloud_drive(QString)));
    connect(ui->cloudDriveDetailsButton, SIGNAL(clicked()), this, SLOT(open_close_details()));
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

void CloudDriveWidget::open_close_details() {
    if (defaultMode) {
        ui->driveName->setVisible(false);
        ui->userName->setVisible(false);
        ui->driveSize->setVisible(false);
        ui->driveLogo->setVisible(false);
        ui->docsLogo->setVisible(true);
        ui->docsInfo->setVisible(true);
        ui->photoLogo->setVisible(true);
        ui->photoInfo->setVisible(true);
        ui->musicLogo->setVisible(true);
        ui->musicInfo->setVisible(true);
        ui->otherLogo->setVisible(true);
        ui->otherInfo->setVisible(true);
        QMap<QString, qint64> distribution = StatisticsUtils::get_types_distribution_by_size(QFileInfo(QDir::homePath() + "/" + ui->driveName->text()));
        ui->docsInfo->setText("Documents\n" + DirectorySizeCalculationUtils::formatSize(distribution.value("Text")));
        ui->photoInfo->setText("Photo\n" + DirectorySizeCalculationUtils::formatSize(distribution.value("Image")));
        ui->musicInfo->setText("Music\n" + DirectorySizeCalculationUtils::formatSize(distribution.value("Audio")));
        ui->otherInfo->setText("Other\n" + DirectorySizeCalculationUtils::formatSize(distribution.value("Other") + distribution.value("Video") + distribution.value("System") +
                               distribution.value("Programming file") + distribution.value("Executable") + distribution.value("Data") + distribution.value("Archive")));
        ui->cloudDriveDetailsButton->setText("Close");
        defaultMode = false;
    }
    else {
        ui->driveName->setVisible(true);
        ui->userName->setVisible(true);
        ui->driveSize->setVisible(true);
        ui->driveLogo->setVisible(true);
        ui->docsLogo->setVisible(false);
        ui->docsInfo->setVisible(false);
        ui->photoLogo->setVisible(false);
        ui->photoInfo->setVisible(false);
        ui->musicLogo->setVisible(false);
        ui->musicInfo->setVisible(false);
        ui->otherLogo->setVisible(false);
        ui->otherInfo->setVisible(false);
        ui->cloudDriveDetailsButton->setText("Details");
        defaultMode = true;
    }
}
