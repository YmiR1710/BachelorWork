#ifndef STATISTICS_H
#define STATISTICS_H

#include <QMap>
#include <QFileInfo>
#include <QDir>
#include <QStorageInfo>
#include <QList>
#include "QDebug"

class StatisticsUtils
{
public:
    static QMap<QString, int> get_types_distribution_by_count(QFileInfo directory);
    static QMap<QString, qint64> get_types_distribution_by_size(QFileInfo directory);
    static QList<QStorageInfo> get_storage_info();

private:
    static const QStringList audio;
    static const QStringList archive;
    static const QStringList data;
    static const QStringList executable;
    static const QStringList image;
    static const QStringList programming_file;
    static const QStringList system;
    static const QStringList video;
    static const QStringList text;
    static QString extension_type_map(QFileInfo file);
};


#endif
