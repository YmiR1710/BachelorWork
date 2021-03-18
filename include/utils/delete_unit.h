#ifndef DELETE_UNIT_H
#define DELETE_UNIT_H

#include "./include/global.h"
#include <QMessageBox>
#include <QFileInfo>

void delete_unit(QString absolutePath, QMessageBox::StandardButton reply, QFileInfo fileInfo);

#endif
