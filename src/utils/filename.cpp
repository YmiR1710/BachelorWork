#include <./include/utils/filename.h>

QString get_filename(QString absolute_path){
    return absolute_path.split("/").last();
}
