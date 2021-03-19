#ifndef DIR_SIZE_H
#define DIR_SIZE_H

#include "./include/global.h"
#include "./include/properties.h"
#include "./include/propertieswindow.h"
#include <QTextEdit>
#include <QDebug>

class DirectorySizeCalculationUtils {
public:
    static void dirSizeWrap(QString dirPath, Properties *properties, PropertiesWindow *widget);
    static QString formatSize(qint64 size);

private:
    static void dirSize(QString dirPath, Properties *properties, PropertiesWindow *widget);
};

#endif
