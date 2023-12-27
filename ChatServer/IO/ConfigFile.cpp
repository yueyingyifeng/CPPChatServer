//
// Created by HP on 2023/12/22.
//


#include "ConfigFile.h"

const string ConfigFile::IP_ {"ip"};
const string ConfigFile::PORT_{ "port" };
const string ConfigFile::PASSWD_{"passwd"};
const string ConfigFile::NAME_{"my_server_name"};

const unordered_map<string, string> ConfigFile::defaultConfigFile = {
        pair<string, string>(PASSWD_,"000"),
        pair<string, string>(IP_,"0.0.0.0"),
		pair<string, string>(PORT_,"56789"),
        pair<string, string>(NAME_,"ChatRoom"),
};

ConfigFile::ConfigFile() {
    configFile = defaultConfigFile;
}

unordered_map<string, string> ConfigFile::getConfigFile(){
    return configFile;
}
//关于n，0是键，1是等于，2是值。0和1必须是对应的，否则为抛出异常重置配置文件
void ConfigFile::readLine(const string& value, int n) {
    static string key;
    if(n == 0){
        if(defaultConfigFile.find(value) == defaultConfigFile.end())
            throw std::runtime_error(string("invalid key at 0 ") + value);
        key = value;
    }
    else if(n == 1){
        if(value != "=")
            throw std::runtime_error(string("invalid key at 1 ") + value);

    }
    else if(n == 2){
        if(!key.empty() && configFile.find(key) != configFile.end())
            configFile[key] = value;
        else
            throw std::runtime_error(string("invalid key at 2 ") + value);
    }
    else
        throw std::runtime_error("an error occur... at ConfigFile::readLine" + __LINE__);
}

string ConfigFile::getValue(const string& key) const{
    if(configFile.find(key) != configFile.end()){
        return configFile.find(key)->second;
    }
    else
        throw std::runtime_error("cannot find the key... at ConfigFile::getValue" + __LINE__);
}

void ConfigFile::setValue(const string& key, string value){
    auto it = configFile.find(key);
    if(it != configFile.end()){
        it->second = value;
    }
    else
        throw std::runtime_error("cannot find the key... at ConfigFile::getValue" + __LINE__);
}