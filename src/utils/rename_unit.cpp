#include <./include/utils/rename_unit.h>

void RenameUtils::rename_unit(QFileInfo info, QString text, bool isFolder)
{
    if (isFolder) {
        rename_folder(info, text);
    } else {
        rename_file(info, text);
    }
}

void RenameUtils::rename_file(QFileInfo info, QString text)
{
    int counter = 1;
    QFile file(info.absoluteFilePath());
    QString new_path = info.absolutePath();
    new_path.append("/");
    new_path.append(text);
    while (!file.rename(new_path)) {
        new_path = info.absolutePath();
        new_path.append("/");
        QStringList text_list = text.split('.');
        text_list[0].append("(");
        text_list[0].append(QString::number(counter));
        text_list[0].append(")");
        new_path.append(text_list.join("."));
        counter++;
    }
}

void RenameUtils::rename_folder(QFileInfo info, QString text)
{
    int counter = 1;
    QDir dir(info.absoluteFilePath());
    QString new_path = info.absolutePath();
    new_path.append("/");
    new_path.append(text);
    while (!dir.rename(info.absoluteFilePath(), new_path)) {
        new_path = info.absolutePath();
        new_path.append("/");
        QStringList text_list = text.split('.');
        text_list[0].append("(");
        text_list[0].append(QString::number(counter));
        text_list[0].append(")");
        new_path.append(text_list.join("."));
        counter++;
    }
}
