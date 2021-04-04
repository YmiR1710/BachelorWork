#ifndef CLOUD_DRIVES_H
#define CLOUD_DRIVES_H

#include "./include/cloud_drive_entity.h"
#include <QList>
#include <QDir>
#include <QFileIconProvider>

class CloudDriveUtils {
public:
    static QList<CloudDrive> get_supported_drives();

private:
    static CloudDrive get_drive(QString path);
    static qint64 get_drive_size(QString path);
    static const QStringList supported_drives;
};

#endif
