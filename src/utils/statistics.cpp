#include "./include/utils/statistics.h"

const QStringList StatisticsUtils::audio = {"aif", "cda", "mid", "midi", "mp3", "mpa", "ogg", "wav", "wma", "wpl"};
const QStringList StatisticsUtils::archive = {"7z", "arj", "deb", "pkg", "rar", "rpm", "gz", "z", "zip"};
const QStringList StatisticsUtils::data = {"csv", "dat", "db", "log", "mdb", "sav", "sql", "xml"};
const QStringList StatisticsUtils::executable = {"apk", "bat", "bin", "com", "exe", "gadget", "jar", "msi", "wsf"};
const QStringList StatisticsUtils::image = {"ai", "bmp", "gif", "ico", "jpeg", "jpg", "png", "ps", "psd", "svg", "tif", "tiff"};
const QStringList StatisticsUtils::programming_file = {"c", "cgi", "pl", "class", "cpp", "cs", "h", "java", "php", "py", "sh", "swift", "vb"};
const QStringList StatisticsUtils::system = {"bak", "cab", "cfg", "cpl", "cur", "dll", "dmp", "drv", "icns", "ico", "ini", "lnk", "msi", "sys", "tmp"};
const QStringList StatisticsUtils::video = {"3g2", "3gp", "avi", "flv", "h264", "m4v", "mkv", "mov", "mp4", "mpg", "mpeg", "rm", "swf", "vob", "wmv"};
const QStringList StatisticsUtils::text = {"doc", "docx", "odt", "pdf", "rtf", "tex", "txt", "wpd"};

QString StatisticsUtils::extension_type_map(QFileInfo file)
{
    if ( file.isDir()) {
        return "Folder";
    }
    QString extension = file.suffix();
    if (audio.contains(extension, Qt::CaseInsensitive))
        return "Audio";
    else if (archive.contains(extension, Qt::CaseInsensitive))
        return "Archive";
    else if (data.contains(extension, Qt::CaseInsensitive))
        return "Data";
    else if (executable.contains(extension, Qt::CaseInsensitive))
        return "Executable";
    else if (image.contains(extension, Qt::CaseInsensitive))
        return "Image";
    else if (programming_file.contains(extension, Qt::CaseInsensitive))
        return "Programming file";
    else if (system.contains(extension, Qt::CaseInsensitive))
        return "System";
    else if (video.contains(extension, Qt::CaseInsensitive))
        return "Video";
    else if (text.contains(extension, Qt::CaseInsensitive))
        return "Text";
    else
        return "Other";
}

QMap<QString, int> StatisticsUtils::get_types_distribution_by_count(QFileInfo directory)
{
    QDir dir(directory.absoluteFilePath());
    QMap<QString, int> typesMap;
    QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
    for (QFileInfo entry : entries) {
        QString type = extension_type_map(entry);
        if (typesMap.contains(type)) {
            typesMap[type]++;
        } else {
            typesMap[type] = 1;
        }
    }
    return typesMap;
}

QMap<QString, qint64> StatisticsUtils::get_types_distribution_by_size(QFileInfo directory)
{
    QDir dir(directory.absoluteFilePath());
    QMap<QString, qint64> typesMap;
    QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
    for (QFileInfo entry : entries) {
        QString type = extension_type_map(entry);
        if (!entry.isDir()) {
            if (typesMap.contains(type)) {
                typesMap[type] += entry.size();
            } else {
                typesMap[type] = entry.size();
            }
        }
    }
    return typesMap;
}

QList<QStorageInfo> StatisticsUtils::get_storage_info()
{
    return QStorageInfo::root().mountedVolumes();
}
