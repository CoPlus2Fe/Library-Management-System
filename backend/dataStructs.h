#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <string>

// 图书结构体
struct Book {
    std::string bookId;    // 图书ID（唯一）
    std::string name;      // 书名
    std::string author;    // 作者
    std::string press;     // 出版社
    bool isBorrowed;       // 是否借出
};

// 读者结构体
struct Reader {
    std::string readerId;  // 读者ID（唯一）
    std::string name;      // 姓名
    int phone;               // 联系方式
    std::string school;     // 学院
};

// 借阅记录结构体
struct BorrowRecord {
    std::string recordId;  // 借阅记录ID（唯一）
    std::string bookId;    // 图书ID
    std::string readerId;  // 读者ID
    std::string borrowDate;// 借阅日期（YYYY-MM-DD）
    std::string returnDate;// 归还日期（未归还为空）
};

#endif // DATA_STRUCTS_H