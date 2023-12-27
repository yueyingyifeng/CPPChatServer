/*
* 			Author : yyyf
* 		CreateDate : 2023/12/24 12:13:45
* 	   Description ：
*/
#ifndef H_ConfigManager
#define H_ConfigManager

#include <fstream>
#include "ConfigFile.h"

using std::ofstream;
using std::ifstream;

class ConfigManager {
    static const char* CONFIG_FILE_NAME;
    ConfigFile* configFile;
    bool fileExist{false};
public:
    ConfigManager();

    void createConfigFile();

    bool checkConfigFile();

    void loadConfigFile();

    void saveConfigFile();

    ConfigFile* getConfigFile();

};


#endif  