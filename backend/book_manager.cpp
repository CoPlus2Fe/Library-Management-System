#include "book_manager.h"
#include "config.h"
#include "utility.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

// 加载所有图书（从CSV读取）
std::vector<Book> loadAllBooks() {
    std::vector<Book> books;
    checkAndCreateFile(BOOKS_PATH);

    std::ifstream file(BOOKS_PATH);
    std::string line;
    // 跳过首行（表头）
    getline(file, line);
    while (getline(file, line)) {
        std::vector<std::string> fields = splitCsvLine(line);
        if (fields.size() == 5) {
            Book book;
            book.bookId = fields[0];
            book.name = fields[1];
            book.author = fields[2];
            book.press = fields[3];
            book.isBorrowed = (fields[4] == "1") ? true : false;
            books.push_back(book);
        }
    }
    file.close();
    return books;
}

// 保存所有图书（写入CSV）
void saveAllBooks(const std::vector<Book>& books) {
    std::ofstream file(BOOKS_PATH);
    // 写入表头
    file << "图书ID,书名,作者,出版社,是否借出" << std::endl;
    for (const auto& book : books) {
        file << book.bookId << ","
            << book.name << ","
            << book.author << ","
            << book.press << ","
            << (book.isBorrowed ? "1" : "0") << std::endl;
    }
    file.close();
}

// 新增图书
void addBook() {
    std::vector<Book> books = loadAllBooks();
    Book newBook;

    std::cout << "===== 新增图书 =====" << std::endl;
    std::cout << "请输入图书ID（唯一）：";
    std::cin >> newBook.bookId;

    // 检查ID是否重复
    for (const auto& book : books) {
        if (book.bookId == newBook.bookId) {
            std::cout << "错误：图书ID已存在！" << std::endl;
            return;
        }
    }

    std::cin.ignore(); // 清空缓冲区
    std::cout << "请输入书名：";
    std::getline(std::cin, newBook.name);
    std::cout << "请输入作者：";
    std::getline(std::cin, newBook.author);
    std::cout << "请输入出版社：";
    std::getline(std::cin, newBook.press);
    newBook.isBorrowed = false; // 默认未借出

    books.push_back(newBook);
    saveAllBooks(books);
    std::cout << "图书新增成功！" << std::endl;
}

// 查询图书（按ID/书名）
void queryBook() {
    std::vector<Book> books = loadAllBooks();
    int choice;
    std::string keyword;

    std::cout << "===== 查询图书 =====" << std::endl;
    std::cout << "1. 按图书ID查询" << std::endl;
    std::cout << "2. 按书名查询" << std::endl;
    std::cout << "请选择查询方式：";
    std::cin >> choice;
    std::cin.ignore();
    std::cout << "请输入查询关键词：";
    std::getline(std::cin, keyword);

    bool found = false;
    std::cout << "\n===== 查询结果 =====" << std::endl;
    std::cout << "图书ID\t书名\t\t作者\t\t出版社\t\t是否借出" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    for (const auto& book : books) {
        if ((choice == 1 && book.bookId == keyword) ||
            (choice == 2 && book.name.find(keyword) != std::string::npos)) {
            std::cout << book.bookId << "\t"
                << book.name << "\t\t"
                << book.author << "\t\t"
                << book.press << "\t\t"
                << (book.isBorrowed ? "已借出" : "未借出") << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "未找到匹配的图书！" << std::endl;
    }
}

// 展示所有书籍
void showAllBooks() {
    std::vector<Book> books = loadAllBooks();
    std::cout << "\n===== 图书馆所有书籍列表 =====" << std::endl;

    // 处理无图书的情况
    if (books.empty()) {
        std::cout << "当前图书馆暂无任何图书！" << std::endl;
        return;
    }

    // 格式化输出表头
    std::cout << std::left; // 左对齐
    std::cout << std::setw(10) << "图书ID"
        << std::setw(30) << "书名"
        << std::setw(20) << "作者"
        << std::setw(25) << "出版社" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;

    // 遍历输出所有图书
    for (const auto& book : books) {
        std::cout << std::setw(10) << book.bookId
            << std::setw(30) << book.name
            << std::setw(20) << book.author
            << std::setw(25) << book.press << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "总计：" << books.size() << " 本图书" << std::endl;
}