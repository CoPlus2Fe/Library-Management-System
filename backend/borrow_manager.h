#ifndef BORROW_MANAGER_H
#define BORROW_MANAGER_H

#include "data_structures.h"
#include <vector>

// 加载所有借阅记录
std::vector<BorrowRecord> loadAllRecords();

// 保存所有借阅记录
void saveAllRecords(const std::vector<BorrowRecord>& records);

// 图书借阅
void borrowBook();

// 图书归还
void returnBook();

#endif // BORROW_MANAGER_H#pragma once
