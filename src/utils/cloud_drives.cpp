#include "./include/utils/cloud_drives.h"

const QStringList CloudDriveUtils::supported_drives = {"/OneDrive"};

QList<CloudDrive> CloudDriveUtils::get_supported_drives()
{
    QList<CloudDrive> drives;
    for (auto drive : supported_drives) {
        QString path = QDir::homePath().append(drive);
        if (QDir(path).exists()) {
            drives.append(get_drive(path));
        }
    }
    return drives;
}

CloudDrive CloudDriveUtils::get_drive(QString path)
{
    QFileInfo driveInfo(path);
    CloudDrive drive;
    QFileIconProvider iconProvider;
    drive.setName(driveInfo.baseName());
    drive.setPath(path);
    drive.setImage(iconProvider.icon(driveInfo).pixmap(QSize(32, 32)));
    drive.setSize(get_drive_size(path));
    return drive;
}

qint64 CloudDriveUtils::get_drive_size(QString path)
{
    qint64 size = 0;
    QDir dir(path);
    QDir::Filters fileFilters = QDir::Files | QDir::System | QDir::Hidden;
    for (QString filePath : dir.entryList(fileFilters)) {
        QFileInfo fi(dir, filePath);
        size += fi.size();
    }
    QDir::Filters dirFilters = QDir::Dirs | QDir::NoDotAndDotDot | QDir::System | QDir::Hidden;
    for (QString childDirPath : dir.entryList(dirFilters))
        size += get_drive_size(path + QDir::separator() + childDirPath);
    return size;
}
