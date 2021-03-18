#include <./include/utils/copypaste.h>

void paste_unit(QFileInfo copy_info, QFileInfo chosen_info, bool isFolder) {
    if (isFolder) {
        QDir dir_to_copy(copy_info.absoluteFilePath());
        if (dir_to_copy.exists()) {
            QString new_path = chosen_info.absolutePath();
            QString src_path = copy_info.absoluteFilePath();
            new_path.append("/");
            new_path.append(copy_info.baseName());
            if (!copy_info.completeSuffix().isEmpty()) {
                new_path.append(".");
            }
            new_path.append(copy_info.completeSuffix());
            copyPath(src_path, new_path);
        }
    } else {
        QFile file_to_copy(copy_info.absoluteFilePath());
        if (file_to_copy.exists()) {
            QString new_path = chosen_info.absolutePath();
            new_path.append("/");
            new_path.append(copy_info.baseName());
            if (copy_info.completeSuffix().size() != 0) {
                new_path.append(".");
                new_path.append(copy_info.completeSuffix());
            }
            int counter = 1;
            while (!file_to_copy.copy(new_path)) {
                new_path = chosen_info.absolutePath();
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
}
