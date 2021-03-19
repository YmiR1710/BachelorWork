#include <./include/utils/delete_unit.h>

void DeletionUtils::delete_unit(QString absolutePath, QMessageBox::StandardButton reply, QFileInfo fileInfo) {
    if (fileInfo.isFile()) {
        delete_file(absolutePath, reply, fileInfo);
    }
    else if (fileInfo.isSymLink()) {
        delete_file(absolutePath, reply, fileInfo);
    }
    else {
        delete_folder(absolutePath, reply, fileInfo);
    }
}

void DeletionUtils::delete_file(QString absolutePath, QMessageBox::StandardButton reply, QFileInfo fileInfo) {
    QFile file(absolutePath);
    if (reply == QMessageBox::Yes) {
        QFileInfo f(file);
        QString own = f.owner();
        if (f.permission(QFile::WriteUser) && own != "root") {
            file.remove();
        } else {
            QMessageBox messageBox;
            messageBox.setText("No permission");
            messageBox.setFixedSize(500, 200);
            messageBox.exec();
        }
    }
}

void DeletionUtils::delete_folder(QString absolutePath, QMessageBox::StandardButton reply, QFileInfo fileInfo) {
    QDir dir(absolutePath);
    if (reply == QMessageBox::Yes) {
        QFileInfo f(dir.absolutePath());
        QString own = f.owner();
        if (f.permission(QFile::WriteUser) && own != "root") {
            dir.removeRecursively();
        } else {
            QMessageBox messageBox;
            messageBox.setText("No permission");
            messageBox.setFixedSize(500, 200);
            messageBox.exec();
        }
    }
}
