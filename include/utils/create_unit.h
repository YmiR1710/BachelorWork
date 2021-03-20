#ifndef CREATE_UNIT_H
#define CREATE_UNIT_H

#include "./include/global.h"
#include <QString>
#include <QDir>

class CreationUtils {
public:
    static void create_unit(QString text, QString path, bool isFolder);

private:
    static void create_folder(QString text, QString path);
    static void create_file(QString text, QString path);
};



#endif
