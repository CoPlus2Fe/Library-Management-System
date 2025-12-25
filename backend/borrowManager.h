#ifndef BORROW_MANAGER_H
#define BORROW_MANAGER_H

#include "bookManager.h"
#include "readerManager.h"
#include "dataStructs.h"

class BorrowManager {
private:
    BookManager& bookMgr;       // 依赖注入：图书管理
    readerManager& readerMgr;   // 依赖注入：读者管理

    // 内部加载借阅记录
    std::vector<borrowRecord> loadAllRecordsInternal();
    // 内部保存借阅记录
    void saveAllRecordsInternal(const std::vector<borrowRecord>& records);
    // 生成唯一借阅ID
    std::string generateRecordId();

public:
    // 构造函数（注入依赖）
    BorrowManager(BookManager& bMgr, readerManager& rMgr)
        : bookMgr(bMgr), readerMgr(rMgr) {
    }

    // 图书借阅
    void borrowBook();
    // 图书归还
    void returnBook();
};

#endif // BORROW_MANAGER_H