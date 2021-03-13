#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QListView>
#include <QFileInfo>
#include <QDir>
#include <QLineEdit>
#include "./include/global.h"

void open_folder(QFileSystemModel* model, QListView* listView, QLineEdit* lineEdit, QFileInfo fileInfo, const QModelIndex &index);

#endif
