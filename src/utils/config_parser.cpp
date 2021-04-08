#include "./include/utils/config_parser.h"

const std::string ConfigParser::CONFIG_LOCATION = "./config/.config";
const std::string ConfigParser::TEMP_CONFIG_LOCATION = "./config/.config.temp";


void ConfigParser::configure()
{
    parse_config();
}

void ConfigParser::parse_config()
{
    std::string line;
    std::fstream fileStream(CONFIG_LOCATION);
    while (std::getline(fileStream, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            if (key[0] == '#')
                continue;
            if (std::getline(is_line, value)) {
                if (key == "theme") {
                    if (value == "LIGHT") {
                        currentTheme = Theme::LIGHT;
                    } else if (value == "DARK") {
                        currentTheme = Theme::DARK;
                    } else {
                        currentTheme = Theme::DARK;
                    }
                }
                if (key == "favorites") {
                    for (QString path : QString(value.c_str()).split(",")) {
                        existingFavoritePaths.append(path);
                    }
                }
            }
        }
    }
    fileStream.close();
}

void ConfigParser::change_config(QString key, QString value)
{
    std::ifstream in(CONFIG_LOCATION);
    std::ofstream out(TEMP_CONFIG_LOCATION);
    std::string strTemp;
    const char *delim = "=";
    while (std::getline(in, strTemp)) {
        if (split(strTemp, delim)[0] == key.toStdString()) {
            strTemp = key.append(delim).append(value).toStdString();
        }
        strTemp += "\n";
        out << strTemp;
    }
    in.close();
    out.close();
    std::remove(CONFIG_LOCATION.c_str());
    std::rename(TEMP_CONFIG_LOCATION.c_str(), CONFIG_LOCATION.c_str());
}

std::vector<std::string> ConfigParser::split(const std::string &str, const char *delim)
{
    std::vector<std::string> dest;
    char *pTempStr = strdup( str.c_str() );
    char *pWord = strtok(pTempStr, delim);
    while (pWord != NULL) {
        dest.push_back(pWord);
        pWord = strtok(NULL, delim);
    }
    free(pTempStr);
    return dest;
}

QString ConfigParser::list_to_string(QStringList list)
{
    QString result = "";
    for (QString string : list)
        result.append(string + ",");
    return result.remove(result.size() - 1, 1);
}
