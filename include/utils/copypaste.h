#ifndef COPYPASTE_H
#define COPYPASTE_H

#include <QDir>
#include <QFile>
#include <QString>
#include <QFileInfo>
#include "./include/global.h"
#include "./include/utils/copy_path.h"

class CopyPasteUtils {
public:
    static void paste_unit(QFileInfo copy_info, QFileInfo chosen_info, bool isFolder);

private:
    static void paste_file(QFileInfo copy_info, QFileInfo chosen_info);
    static void paste_folder(QFileInfo copy_info, QFileInfo chosen_info);
};





#endif
