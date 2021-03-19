#ifndef SEARCH_FILTER_H
#define SEARCH_FILTER_H

#include <QStringList>
#include <QFileSystemModel>
#include <QListView>
#include <QLineEdit>

class FiltersUtils {
public:
    static void search_filter(QString item_name, QListView *listView, QLineEdit *lineEdit, QFileSystemModel *model);
};

#endif
