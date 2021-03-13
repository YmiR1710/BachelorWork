#include "./include/utils/dir_size.h"

qint64 dirSize(QString dirPath) {
    qint64 KILOBYTE_CONVERSION = 1000;
    qint64 size = 0;
    QDir dir(dirPath);
    QDir::Filters fileFilters = QDir::Files|QDir::System|QDir::Hidden;
    for(QString filePath : dir.entryList(fileFilters)) {
        QFileInfo fi(dir, filePath);
        size+= fi.size();
    }
    QDir::Filters dirFilters = QDir::Dirs|QDir::NoDotAndDotDot|QDir::System|QDir::Hidden;
    for(QString childDirPath : dir.entryList(dirFilters))
        size+= dirSize(dirPath + QDir::separator() + childDirPath);
    return size/KILOBYTE_CONVERSION;
}
