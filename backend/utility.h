#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>

// 分割CSV行（按逗号分割）
std::vector<std::string> splitCsvLine(const std::string& line);

// 获取当前日期（YYYY-MM-DD）
std::string getCurrentDate();

// 检查文件是否存在（不存在则创建空文件）
void checkAndCreateFile(const std::string& path);

#endif // UTILITY_H#pragma once
