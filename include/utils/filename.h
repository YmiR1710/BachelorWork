#ifndef FILENAME_H
#define FILENAME_H

#include <QString>
#include <QStringList>

class FileNameUtils {
public:
    static QString get_filename(QString absolute_path);
};

#endif
