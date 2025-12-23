#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "data_structs.h"

// 分割CSV行（支持引号包裹的字段）
std::vector<std::string> splitCsvLine(const std::string& line);

// 获取当前日期（YYYY-MM-DD）
std::string getCurrentDate();

// 检查文件是否存在，不存在则创建
void checkAndCreateFile(const std::string& path);

// 检查文件夹是否存在，不存在则创建
void checkAndCreateFolder(const std::string& folderPath);

// 给含逗号的字段加引号（CSV兼容）
std::string wrapQuotes(const std::string& s);

#endif // UTILS_H