#ifndef SEARCH_FILTER_H
#define SEARCH_FILTER_H

#include <QStringList>
#include <QFileSystemModel>
#include <QTableView>
#include <QLineEdit>

class FiltersUtils {
public:
    static void search_filter(QString item_name, QTableView *listView, QLineEdit *lineEdit, QFileSystemModel *model);
};

#endif
