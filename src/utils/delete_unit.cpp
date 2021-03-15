#include <./include/utils/delete_unit.h>

void delete_unit(QString absolutePath, QMessageBox::StandardButton reply, QFileInfo fileInfo){
    if(fileInfo.isFile()){
        QFile file(absolutePath);
        if (reply == QMessageBox::Yes) {
            QFileInfo f(file);
            QString own = f.owner();
            if (f.permission(QFile::WriteUser) && own != "root"){
                file.remove();
            }else{
                QMessageBox messageBox;
                messageBox.setText("No permission");
                messageBox.setFixedSize(500,200);
                messageBox.exec();
            }
        }
    }
    else if(fileInfo.isSymLink()){
        QFile file(absolutePath);
        if (reply == QMessageBox::Yes) {
            QFileInfo f(file);
            QString own = f.owner();
            if (f.permission(QFile::WriteUser) && own != "root"){
                file.remove();
            }else{
                QMessageBox messageBox;
                messageBox.setText("No permission");
                messageBox.setFixedSize(500,200);
                messageBox.exec();
            }
        }
    }
    else{
        QDir dir(absolutePath);
        if (reply == QMessageBox::Yes) {
            QFileInfo f(dir.absolutePath());
            QString own = f.owner();
            if (f.permission(QFile::WriteUser) && own != "root"){
                dir.removeRecursively();
            }else{
                QMessageBox messageBox;
                messageBox.setText("No permission");
                messageBox.setFixedSize(500,200);
                messageBox.exec();
            }
        }
    }
}
