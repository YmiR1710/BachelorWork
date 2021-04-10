#include <./include/utils/copypaste.h>

void CopyPasteUtils::paste_unit(QFileInfo copy_info, QString path, bool isFolder)
{
    if (isFolder) {
        paste_folder(copy_info, path);
    } else {
        paste_file(copy_info, path);
    }
}

void CopyPasteUtils::paste_file(QFileInfo copy_info, QString path)
{
    QFile file_to_copy(copy_info.absoluteFilePath());
    if (file_to_copy.exists()) {
        QString new_path = path;
        new_path.append("/");
        new_path.append(copy_info.baseName());
        if (copy_info.completeSuffix().size() != 0) {
            new_path.append(".");
            new_path.append(copy_info.completeSuffix());
        }
        int counter = 1;
        while (!file_to_copy.copy(new_path)) {
            new_path = path;
            new_path.append("/");
            QString text = copy_info.baseName();
            if (copy_info.completeSuffix().size() != 0) {
                text.append(".");
                text.append(copy_info.completeSuffix());
            }
            QStringList text_list = text.split('.');
            text_list[0].append("(");
            text_list[0].append(QString::number(counter));
            text_list[0].append(")");
            new_path.append(text_list.join("."));
            counter++;
        }
    }
}

void CopyPasteUtils::paste_folder(QFileInfo copy_info, QString path)
{
    QDir dir_to_copy(copy_info.absoluteFilePath());
    if (dir_to_copy.exists()) {
        QString new_path = path;
        QString src_path = copy_info.absoluteFilePath();
        new_path.append("/");
        new_path.append(copy_info.baseName());
        if (!copy_info.completeSuffix().isEmpty()) {
            new_path.append(".");
        }
        new_path.append(copy_info.completeSuffix());
        CopyPathUtils::copyPath(src_path, new_path);
    }
}
