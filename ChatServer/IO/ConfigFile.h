/*
* 			Author : yyyf
* 		CreateDate : 2023/12/24 12:13:37
* 	   Description ：
*/
#ifndef H_ConfigFile
#define H_ConfigFile

#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::unordered_map;
using std::pair;

class ConfigFile {
    unordered_map<string, string> configFile;
public:
    static const string IP_;
    static const string PASSWD_;
    static const string NAME_;
    static const string MAX_WIDTH_;
    static const string PORT_;
    static const unordered_map<string, string> defaultConfigFile;
    void readLine(const string& value, int n);

    ConfigFile();
    unordered_map<string, string> getConfigFile();
    string getValue(const string& key) const;
    void setValue(const string& key, string value);
};


#endif