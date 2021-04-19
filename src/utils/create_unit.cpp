#include "./include/utils/create_unit.h"

void CreationUtils::create_unit(QString text, QString path, bool isFolder)
{
    QString absolutePath = path;
    path.append("/");
    path.append(text);
    if (isFolder) {
        create_folder(text, path, absolutePath);
    } else {
        create_file(text, path, absolutePath);
    }
}

void CreationUtils::create_file(QString text, QString path, QString absolutePath)
{
    int counter = 1;
    QFile newFile(path);

    if (newFile.exists()) {
        while (true) {
            path = prepare_path(absolutePath, text, counter);
            QFile newFile(path);
            if (!newFile.exists()) {
                newFile.open(QFile::WriteOnly);
                break;
            }
            counter++;
        }
    } else {
        newFile.open(QFile::WriteOnly);
    }
    newFile.close();
}

void CreationUtils::create_folder(QString text, QString path, QString absolutePath)
{
    int counter = 1;
    QDir newFolder(path);
    QString pathCopy = path;
    if (newFolder.exists()) {
        while (true) {
            path = prepare_path(absolutePath, text, counter);
            QDir newFolder(path);
            if (!newFolder.exists()) {
                newFolder.mkpath(".");
                break;
            }
            counter++;
        }
    } else {
        newFolder.mkpath(".");
    }
}

QString CreationUtils::prepare_path(QString path, QString text, int counter)
{
    path.append("/");
    QStringList text_list = text.split('.');
    text_list[0].append("(");
    text_list[0].append(QString::number(counter));
    text_list[0].append(")");
    path.append(text_list.join("."));
    return path;
}
