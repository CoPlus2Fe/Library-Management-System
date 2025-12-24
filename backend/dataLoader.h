#pragma once
#include <vector>
#include <string>
#include "./cf/recommender.h"   // 为了 BorrowRecord

using std::vector;
using std::string;

// 从 CSV 读取借阅记录
vector<borrowRecord> loadBorrowRecords(const string& filename);
