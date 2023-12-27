//
// Created by HP on 2023/12/22.
//

#include "ConfigManager.h"

const char* ConfigManager::CONFIG_FILE_NAME = "ServerConfig.ini";

ConfigManager::ConfigManager() {
    configFile = new ConfigFile();
    if(checkConfigFile())
        loadConfigFile();
    else
        createConfigFile();
}

void ConfigManager::createConfigFile() {
    ofstream ofs(CONFIG_FILE_NAME);
    for(pair<string,string> l : ConfigFile::defaultConfigFile){
        ofs << l.first << " = " << l.second << std::endl;
    }
    ofs.close();
}

bool ConfigManager::checkConfigFile() {
    ifstream i(CONFIG_FILE_NAME);

    if(!i.good()){
        i.close();
        return false;
    }
    i.close();
    return true;
}

void ConfigManager::loadConfigFile() {
    ifstream ifs(CONFIG_FILE_NAME);
    string word;
    for(int n{0}; ifs >> word; ){
        configFile->readLine(word,n++);
        if(n == 3)
            n = 0;
    }

    ifs.close();
}

void ConfigManager::saveConfigFile(){
    ofstream ofs(CONFIG_FILE_NAME);
    for(pair<string,string> p : configFile->getConfigFile())
        ofs << p.first << " = " << p.second << std::endl;
    ofs.close();
}

ConfigFile* ConfigManager::getConfigFile()
{
    return configFile;
}

