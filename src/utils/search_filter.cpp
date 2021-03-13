#include <./include/utils/search_filter.h>

void search_filter(QString item_name, QListView* listView, QLineEdit* lineEdit, QFileSystemModel *model){
    QStringList filters;
    QString request = "*";
    request.append(item_name);
    request.append("*");
    filters << request;
    filters << ".";
    filters << "..";
    model->setNameFilters(filters);
    model->setNameFilterDisables(false);
    listView->setRootIndex(model->index(lineEdit->text()));
}
