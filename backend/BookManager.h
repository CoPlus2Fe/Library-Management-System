#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H

#include <vector>
#include <string>
#include "data_structs.h"
#include "config.h"

class BookManager {
private:
    // 内部辅助：加载所有图书（对外通过getAllBooks暴露）
    std::vector<Book> loadAllBooksInternal();
    // 内部辅助：保存所有图书（对外通过saveAllBooksPublic暴露）
    void saveAllBooksInternal(const std::vector<Book>& books);

public:
    // 新增图书
    void addBook();
    // 查询图书（按ID/书名）
    void queryBook();
    // 展示所有图书
    void showAllBooks();
    // 对外暴露：获取所有图书（解决C2248错误）
    std::vector<Book> getAllBooks();
    // 对外暴露：保存图书（解决C2248错误）
    void saveAllBooksPublic(const std::vector<Book>& books);
    // 按ID查询图书详情
    Book getBookById(const std::string& bookId);
    // 更新图书借阅状态
    bool updateBookBorrowStatus(const std::string& bookId, bool isBorrowed);
};

#endif // BOOK_MANAGER_H