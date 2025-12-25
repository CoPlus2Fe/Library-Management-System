#ifndef DATASTRUCTS_H   //作用是防止头文件被多重包含
#define DATASTRUCTS_H

#include <string>

using std::string; 

// 图书结构体
struct Book {
    string bookId;    // 图书ID（唯一）
    string name;      // 书名
    string author;    // 作者
    string press;     // 出版社
    bool isBorrowed;       // 是否借出
    std::string class1;//一级分类
    std::string class2; 
};

// 读者结构体
struct Reader {
    string readerId;  // 读者ID（唯一）
    string name;      // 姓名
    int phone;               // 联系方式
    string school;     // 学院
};

// 借阅记录结构体
struct borrowRecord {
    string recordId;  // 借阅记录ID（唯一）
    string book_id;    // 图书ID
    string user_id;  // 读者ID
    string borrowDate;// 借阅日期（YYYY-MM-DD）
    string returnDate;// 归还日期（未归还为空）
    int renewCount;   // 续借次数
};

#endif // DATA_STRUCTS_H