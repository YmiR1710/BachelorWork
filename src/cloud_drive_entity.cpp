#include "./include/cloud_drive_entity.h"

void CloudDrive::setName(QString name) {
    this->name = name;
}

QString CloudDrive::getName() {
    return name;
}

void CloudDrive::setPath(QString path) {
    this->path = path;
}

QString CloudDrive::getPath() {
    return path;
}

void CloudDrive::setSize(qint64 size) {
    this->size = size;
}

qint64 CloudDrive::getSize() {
    return size;
}

void CloudDrive::setImage(QPixmap image) {
    this->image = image;
}

QPixmap CloudDrive::getImage() {
    return image;
}
