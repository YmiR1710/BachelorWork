#ifndef RENAME_UNIT_H
#define RENAME_UNIT_H

#include <QDir>
#include <QFile>
#include <QString>

class RenameUtils {
public:
    static void rename_unit(QFileInfo info, QString text, bool isFolder);

private:
    static void rename_file(QFileInfo info, QString text);
    static void rename_folder(QFileInfo info, QString text);
};

#endif
