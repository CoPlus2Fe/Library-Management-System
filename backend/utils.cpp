#include "utils.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <io.h>         //在其他系统上需要改为#include <unistd.h>
#include <direct.h>     //在其他系统上需要改为#include <sys/stat.h>
#include <cstdio>

using namespace std;

vector<string> splitCsvLine(const string& line) {
    vector<string> res;
    string temp;
    bool inQuotes = false;
    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        }
        else if (c == ',' && !inQuotes) {
            res.push_back(temp);
            temp.clear();
        }
        else {
            temp += c;
        }
    }
    res.push_back(temp);
    return res;
}

string getCurrentDate() {
    time_t now = time(0);
    tm ltm{};
    localtime_s(&ltm, &now);
    char buffer[20];
    sprintf_s(buffer, sizeof(buffer), "%04d-%02d-%02d",
        1900 + ltm.tm_year, 1 + ltm.tm_mon, ltm.tm_mday);
    return string(buffer);
}

void checkAndCreateFile(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        ofstream newFile(path);
        if (newFile.is_open()) {
            newFile.close();
            cout << "文件不存在，已创建：" << path << endl;
        }
        else {
            cout << "错误：无法创建文件 " << path << endl;
        }
    }
    file.close();
}

void checkAndCreateFolder(const string& folderPath) {
    if (_access(folderPath.c_str(), 0) == -1) {
        if (_mkdir(folderPath.c_str()) == 0) {
            cout << "文件夹不存在，已创建：" << folderPath << endl;
        }
        else {
            cout << "错误：无法创建文件夹 " << folderPath << endl;
        }
    }
}

string wrapQuotes(const string& s) {
    return (s.find(',') != string::npos) ? ("\"" + s + "\"") : s;
}