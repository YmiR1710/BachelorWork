#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "./include/global.h"
#include <fstream>
#include <sstream>
#include <QString>

class ConfigParser
{

private:
    static const std::string CONFIG_LOCATION;
    static const std::string TEMP_CONFIG_LOCATION;
    static void parse_theme();
    static std::vector<std::string> split(const std::string &str, const char *delim);

public:
    static void configure();
    static void change_config(QString key, QString value);
};

#endif
