#pragma once
#include <vector>
#include <string>
#include "dataStructs.h"

using std::vector;
using std::string;

// 从 CSV 读取借阅记录
vector<borrowRecord> loadBorrowRecords(const string& filename);
