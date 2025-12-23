#ifndef READER_MANAGER_H
#define READER_MANAGER_H

#include "data_structures.h"
#include <vector>

// 加载所有读者（从CSV读取）
std::vector<Reader> loadAllReaders();

// 保存所有读者（写入CSV）
void saveAllReaders(const std::vector<Reader>& readers);

// 新增读者
void addReader();

#endif // READER_MANAGER_H#pragma once
