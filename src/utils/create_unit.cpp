#include "./include/utils/create_unit.h"

void create_unit(QString text, bool isFolder) {
    int counter = 1;
    QString path = model_1->fileInfo(chosenFile).absolutePath();
    path.append("/");
    path.append(text);
    if (isFolder) {
        QDir newFolder(path);
        if (newFolder.exists()) {
            while (true) {
                path = model_1->fileInfo(chosenFile).absolutePath();
                path.append("/");
                QStringList text_list = text.split('.');
                text_list[0].append("(");
                text_list[0].append(QString::number(counter));
                text_list[0].append(")");
                path.append(text_list.join("."));
                QDir newFolder(path);
                if (!newFolder.exists()) {
                    newFolder.mkpath(".");
                    break;
                }
                counter++;
            }
        }
        else {
            newFolder.mkpath(".");
        }
    }
    else {
        QString path = model_1->fileInfo(chosenFile).absolutePath();
        path.append("/");
        path.append(text);
        QFile newFile(path);
        if (newFile.exists()) {
            while (true) {
                path = model_1->fileInfo(chosenFile).absolutePath();
                path.append("/");
                QStringList text_list = text.split('.');
                text_list[0].append("(");
                text_list[0].append(QString::number(counter));
                text_list[0].append(")");
                path.append(text_list.join("."));
                QFile newFile(path);
                if (!newFile.exists()) {
                    newFile.open(QFile::WriteOnly);
                    break;
                }
                counter++;
            }
        }
        else {
            newFile.open(QFile::WriteOnly);
        }
        newFile.close();
    }
}
