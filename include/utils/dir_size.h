#ifndef DIR_SIZE_H
#define DIR_SIZE_H

#include "./include/global.h"
#include "./include/properties.h"
#include "./include/propertieswindow.h"
#include <QTextEdit>
#include <QDebug>

void dirSizeWrap(QString dirPath, Properties *properties, PropertiesWindow *widget);

void dirSize(QString dirPath, Properties *properties, PropertiesWindow *widget);

QString formatSize(qint64 size);

#endif
