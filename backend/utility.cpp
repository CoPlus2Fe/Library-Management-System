#include "utility.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdio>
#include <iostream>
// 分割CSV行（按逗号分割）
std::vector<std::string> splitCsvLine(const std::string& line) {
    std::vector<std::string> res;
    std::stringstream ss(line);
    std::string temp;
    while (getline(ss, temp, ',')) {
        res.push_back(temp);
    }
    return res;
}

// 获取当前日期（YYYY-MM-DD）
std::string getCurrentDate() {
    time_t now = time(0);
    tm ltm{}; // 初始化空结构体
    localtime_s(&ltm, &now); // 安全版本localtime_s
    char buffer[20];
    // 安全版本sprintf_s，指定缓冲区大小
    sprintf_s(buffer, sizeof(buffer), "%04d-%02d-%02d",
        1900 + ltm.tm_year, 1 + ltm.tm_mon, ltm.tm_mday);
    return std::string(buffer);
}

// 检查文件是否存在（不存在则创建空文件）
void checkAndCreateFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::ofstream newFile(path);
        newFile.close();
        std::cout << "文件不存在，已创建空文件：" << path << std::endl;
    }
    file.close();
}