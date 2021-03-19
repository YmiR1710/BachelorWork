#ifndef CREATE_UNIT_H
#define CREATE_UNIT_H

#include "./include/global.h"
#include <QString>
#include <QDir>

class CreationUtils {
public:
    static void create_unit(QString text, bool isFolder);

private:
    static void create_folder(QString text);
    static void create_file(QString text);
};



#endif
