#ifndef COPYPASTE_H
#define COPYPASTE_H

#include "./include/global.h"
#include "./include/utils/copy_path.h"
#include <QDir>
#include <QFile>
#include <QString>
#include <QFileInfo>

class CopyPasteUtils {
public:
    static void paste_unit(QFileInfo copy_info, QString path, bool isFolder);

private:
    static void paste_file(QFileInfo copy_info, QString path);
    static void paste_folder(QFileInfo copy_info, QString path);
};





#endif
