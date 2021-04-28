#include "./include/utils/create_unit.h"

QString CreationUtils::create_unit(QString text, QString path, bool isFolder)
{
    QString absolutePath = path;
    path.append("/");
    path.append(text);
    if (isFolder) {
        return create_folder(text, path, absolutePath);
    } else {
        return create_file(text, path, absolutePath);
    }
}

QString CreationUtils::create_file(QString text, QString path, QString absolutePath)
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
    return path;
}

QString CreationUtils::create_folder(QString text, QString path, QString absolutePath)
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
    return path;
}

void CreationUtils::create_folder_from_files(QString path) {
    for (auto &c_file : copiedFiles) {
        QFileInfo copy_info = model_1->fileInfo(c_file);
        if (copy_info.isDir() && !copy_info.isSymLink()) {
            CopyPasteUtils::paste_unit(copy_info, path, true);
        } else {
            CopyPasteUtils::paste_unit(copy_info, path, false);
        }
        if (to_cut) {
            if (model_1->fileInfo(c_file).isDir() && !model_1->fileInfo(c_file).isSymLink()) {
                QDir dir(model_1->fileInfo(c_file).absoluteFilePath());
                dir.removeRecursively();
            } else {
                QFile file(model_1->fileInfo(c_file).absoluteFilePath());
                file.remove();
            }
        }
    }
    to_cut = false;
    copiedFiles.clear();
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
