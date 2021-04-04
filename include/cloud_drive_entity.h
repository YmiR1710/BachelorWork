#ifndef CLOUD_DRIVE_ENTITY_H
#define CLOUD_DRIVE_ENTITY_H

#include <QString>
#include <QPixmap>

class CloudDrive {
private:
    QString name;
    QString path;
    QPixmap image;
    qint64 size;

public:
    void setName(QString name);

    QString getName();

    void setPath(QString path);

    QString getPath();

    void setSize(qint64 size);

    qint64 getSize();

    void setImage(QPixmap image);

    QPixmap getImage();
};

#endif
