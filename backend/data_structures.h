#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <string>

// 图书信息结构体
struct Book {
    std::string bookId;    // 图书ID（唯一）
    std::string name;      // 书名
    std::string author;    // 作者
    std::string press;     // 出版社
    bool isBorrowed;       // 是否借出
};

// 读者信息结构体
struct Reader {
    std::string readerId;  // 读者ID（唯一）
    std::string name;      // 姓名
    int age;               // 年龄
    std::string phone;     // 联系方式
};

// 借阅记录结构体
struct BorrowRecord {
    std::string recordId;  // 借阅记录ID（唯一）
    std::string bookId;    // 图书ID
    std::string readerId;  // 读者ID
    std::string borrowDate;// 借阅日期（格式：YYYY-MM-DD）
    std::string returnDate;// 归还日期（未归还为空）
};

#endif // DATA_STRUCTURES_H#pragma once
