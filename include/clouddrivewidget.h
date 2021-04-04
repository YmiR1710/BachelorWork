#ifndef CLOUDDRIVEWIDGET_H
#define CLOUDDRIVEWIDGET_H

#include "../ui/ui_clouddrivewidget.h"
#include "./include/cloud_drive_entity.h"
#include <QWidget>
#include <QDir>
#include <QStyleOption>
#include <QPainter>

namespace Ui {
class CloudDriveWidget;
}

class CloudDriveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CloudDriveWidget(QWidget *parent = nullptr, QString name = "", QPixmap image = QPixmap(), QString size = "");
    ~CloudDriveWidget();

protected:
    virtual void mousePressEvent (QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Ui::CloudDriveWidget *ui;

signals:
    void clicked(QString path);
};

#endif
