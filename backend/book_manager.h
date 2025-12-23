#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H

#include "data_structures.h"
#include <vector>

// 加载所有图书（从CSV读取）
std::vector<Book> loadAllBooks();

// 保存所有图书（写入CSV）
void saveAllBooks(const std::vector<Book>& books);

// 新增图书
void addBook();

// 查询图书（按ID/书名）
void queryBook();

// 展示所有书籍
void showAllBooks();

#endif // BOOK_MANAGER_H#pragma once
