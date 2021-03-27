#ifndef GLOBAL_H
#define GLOBAL_H

#include "panels.h"
#include "themes.h"
#include <QFileSystemModel>
#include <QColor>
#include <QList>

extern QModelIndex chosenFile;
extern QModelIndex copiedFile;
extern QList<QModelIndex> chosenFiles;
extern QList<QModelIndex> copiedFiles;
extern bool to_cut;
extern QFileSystemModel *model_1;
extern QFileSystemModel *model_2;
extern qint64 directorySize;
extern Panel active_panel;
extern Theme currentTheme;
extern QList<QColor> colorTheme;

#endif
