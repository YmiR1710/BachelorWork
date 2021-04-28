#ifndef CREATE_UNIT_H
#define CREATE_UNIT_H

#include "./include/global.h"
#include "./include/utils/copypaste.h"
#include <QString>
#include <QDir>

class CreationUtils {
public:
    static QString create_unit(QString text, QString path, bool isFolder);
    static void create_folder_from_files(QString path);

private:
    static QString create_folder(QString text, QString path, QString absolutePath);
    static QString create_file(QString text, QString path, QString absolutePath);
    static QString prepare_path(QString path, QString text, int counter);
};



#endif
