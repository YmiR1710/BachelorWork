#include "./include/utils/dir_size.h"

void DirectorySizeCalculationUtils::dirSizeWrap(QString dirPath, Properties *properties, PropertiesWindow *widget)
{
    dirSize(dirPath, properties, widget);
    directorySize = 0;
}

void DirectorySizeCalculationUtils::dirSize(QString dirPath, Properties *properties, PropertiesWindow *widget)
{
    bool wasActive = false;
    QDir dir(dirPath);
    QDir::Filters fileFilters = QDir::Files | QDir::System | QDir::Hidden;
    for (QString filePath : dir.entryList(fileFilters)) {
        QFileInfo fi(dir, filePath);
        directorySize += fi.size();
    }
    QDir::Filters dirFilters = QDir::Dirs | QDir::NoDotAndDotDot | QDir::System | QDir::Hidden;
    for (QString childDirPath : dir.entryList(dirFilters)) {
        properties->setSize(formatSize(directorySize));
        if (widget->isActiveWindow()) {
            wasActive = true;
        }
        if (!widget->isActiveWindow() && wasActive) {
            return;
        }
        emit widget->changeTextSignal(properties->toString());
        dirSize(dirPath + QDir::separator() + childDirPath, properties, widget);
    }
}

QString DirectorySizeCalculationUtils::formatSize(qint64 size)
{
    QStringList units = {"Bytes", "KB", "MB", "GB", "TB", "PB"};
    int i;
    double outputSize = size;
    for (i = 0; i < units.size() - 1; i++) {
        if (outputSize < 1024) break;
        outputSize = outputSize / 1024;
    }
    return QString("%0 %1").arg(outputSize, 0, 'f', 2).arg(units[i]);
}

QString DirectorySizeCalculationUtils::getUnit(qint64 size)
{
    QStringList units = {"Bytes", "KB", "MB", "GB", "TB", "PB"};
    int i;
    double outputSize = size;
    for (i = 0; i < units.size() - 1; i++) {
        if (outputSize < 1024) break;
        outputSize = outputSize / 1024;
    }
    return units[i];
}

QString DirectorySizeCalculationUtils::getFormattedSize(qint64 size)
{
    QStringList units = {"Bytes", "KB", "MB", "GB", "TB", "PB"};
    int i;
    double outputSize = size;
    for (i = 0; i < units.size() - 1; i++) {
        if (outputSize < 1024) break;
        outputSize = outputSize / 1024;
    }
    return QString("%0").arg(outputSize, 0, 'f', 2);
}
