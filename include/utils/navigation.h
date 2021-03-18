#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "./include/global.h"
#include <QListView>
#include <QFileInfo>
#include <QDir>
#include <QLineEdit>

void open_folder(QFileSystemModel *model, QListView *listView, QLineEdit *lineEdit, QFileInfo fileInfo, const QModelIndex &index);

#endif
