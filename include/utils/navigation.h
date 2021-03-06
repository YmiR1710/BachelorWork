#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "./include/global.h"
#include "./include/utils/statistics.h"
#include <QTableView>
#include <QFileInfo>
#include <QDir>
#include <QLineEdit>

class NavigationUtils {
public:
    static void open_folder(QFileSystemModel *model, QTableView *listView, QLineEdit *lineEdit, QFileInfo fileInfo);
};

#endif
