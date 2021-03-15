#ifndef DELETE_UNIT_H
#define DELETE_UNIT_H

#include <QMessageBox>
#include <QFileInfo>
#include "./include/global.h"

void delete_unit(QString absolutePath, QMessageBox::StandardButton reply, QFileInfo fileInfo);

#endif
