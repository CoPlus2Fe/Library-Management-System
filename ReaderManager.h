#ifndef READER_MANAGER_H
#define READER_MANAGER_H

#include <vector>
#include <string>
#include "data_structs.h"

class ReaderManager {
private:
    // 内部加载读者
    std::vector<Reader> loadAllReadersInternal();
    // 内部保存读者
    void saveAllReadersInternal(const std::vector<Reader>& readers);

public:
    // 新增读者
    void addReader();
    // 检查读者是否存在（解决VCR001错误）
    bool isReaderExist(const std::string& readerId);
    // 对外暴露加载读者
    std::vector<Reader> getAllReaders();
};

#endif // READER_MANAGER_H