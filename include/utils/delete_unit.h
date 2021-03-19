#ifndef DELETE_UNIT_H
#define DELETE_UNIT_H

#include <QMessageBox>
#include <QFileInfo>
#include "./include/global.h"

class DeletionUtils {
public:
    static void delete_unit(QString absolutePath, QMessageBox::StandardButton reply, QFileInfo fileInfo);

private:
    static void delete_file(QString absolutePath, QMessageBox::StandardButton reply, QFileInfo fileInfo);
    static void delete_folder(QString absolutePath, QMessageBox::StandardButton reply, QFileInfo fileInfo);
};

#endif
