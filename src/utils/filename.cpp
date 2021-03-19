#include <./include/utils/filename.h>

QString FileNameUtils::get_filename(QString absolute_path) {
    return absolute_path.split("/").last();
}
