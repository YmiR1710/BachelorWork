#include <./include/utils/navigation.h>

void NavigationUtils::open_folder(QFileSystemModel *model, QTableView *listView, QLineEdit *lineEdit, QFileInfo fileInfo, const QModelIndex &index) {
    lineEdit->setText(fileInfo.absoluteFilePath());
    if (fileInfo.fileName() == "..") {
        QDir dir = fileInfo.dir();
        dir.cdUp();
        listView->setRootIndex(model->index(dir.absolutePath()));
    } else if (fileInfo.fileName() == ".") {
        listView->setRootIndex(model->index(""));
    }
    else if (fileInfo.isDir()) {
        listView->setRootIndex(index);
    }
}
