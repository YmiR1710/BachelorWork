#ifndef COPYPASTE_H
#define COPYPASTE_H

#include <QDir>
#include <QFile>
#include <QString>
#include <QFileInfo>
#include "./include/global.h"
#include "./include/utils/copy_path.h"

void paste_unit(QFileInfo copy_info, QFileInfo chosen_info, bool isFolder);

#endif
