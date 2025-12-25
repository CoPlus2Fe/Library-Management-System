#include "rank.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

// 内部数据结构（仅模块内使用）
struct BookInfo {
    std::string book_id;
    std::string book_name;
    std::string author;
};

struct BorrowRecordInfo {
    std::string book_id;
};

// 内部工具函数：分割CSV行
static std::vector<std::string> splitCsvLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string current_field;
    bool in_quotes = false;
    for (char c : line) {
        if (c == '"') in_quotes = !in_quotes;
        else if (c == ',' && !in_quotes) {
            fields.push_back(current_field);
            current_field.clear();
        } else current_field += c;
    }
    fields.push_back(current_field);
    return fields;
}

// 内部工具函数：检查并创建文件
static void checkAndCreateFile(const std::string& file_path) {
    std::ifstream file_check(file_path);
    if (!file_check.is_open()) {
        std::ofstream new_file(file_path);
        if (new_file.is_open()) new_file.close();
        else throw std::runtime_error("无法创建文件：" + file_path);
    }
    file_check.close();
}

// 内部函数：加载图书数据
static std::vector<BookInfo> loadBooks(const std::string& books_csv_path) {
    std::vector<BookInfo> books;
    checkAndCreateFile(books_csv_path);
    std::ifstream file(books_csv_path);
    if (!file.is_open()) throw std::runtime_error("无法打开图书文件：" + books_csv_path);

    std::string line;
    int line_num = 0;
    if (std::getline(file, line)) line_num++; // 跳过表头

    while (std::getline(file, line)) {
        line_num++;
        std::vector<std::string> fields = splitCsvLine(line);
        if (fields.size() < 3) {
            std::cerr << "[警告] 图书文件第" << line_num << "行格式错误，跳过" << std::endl;
            continue;
        }
        BookInfo book;
        book.book_id = fields[0];
        book.book_name = fields[1];
        book.author = fields[2];
        books.push_back(book);
    }
    file.close();
    return books;
}

// 内部函数：加载借阅记录
static std::vector<BorrowRecordInfo> loadBorrowRecords(const std::string& borrow_csv_path) {
    std::vector<BorrowRecordInfo> records;
    checkAndCreateFile(borrow_csv_path);
    std::ifstream file(borrow_csv_path);
    if (!file.is_open()) throw std::runtime_error("无法打开借阅记录文件：" + borrow_csv_path);

    std::string line;
    int line_num = 0;
    if (std::getline(file, line)) line_num++; // 跳过表头

    while (std::getline(file, line)) {
        line_num++;
        std::vector<std::string> fields = splitCsvLine(line);
        if (fields.size() < 3) {
            std::cerr << "[警告] 借阅记录第" << line_num << "行格式错误，跳过" << std::endl;
            continue;
        }
        BorrowRecordInfo record;
        record.book_id = fields[2]; // 图书ID在第3列
        records.push_back(record);
    }
    file.close();
    return records;
}

// 核心函数实现（你要调用的就是这个）
void generateTop10BorrowRank(const std::string& books_csv_path, const std::string& borrow_csv_path) {
    try {
        // 1. 加载数据
        std::vector<BookInfo> books = loadBooks(books_csv_path);
        std::vector<BorrowRecordInfo> borrow_records = loadBorrowRecords(borrow_csv_path);

        // 2. 统计借阅次数
        std::map<std::string, int> borrow_count;
        for (const auto& record : borrow_records) {
            if (!record.book_id.empty()) borrow_count[record.book_id]++;
        }

        // 3. 排序
        std::vector<std::pair<std::string, int>> sorted_count(borrow_count.begin(), borrow_count.end());
        std::sort(sorted_count.begin(), sorted_count.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });

        // 4. 输出排行榜
        std::cout << "\n========================================" << std::endl;
        std::cout << "          图书借阅次数TOP10排行榜          " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << std::left << std::setw(5) << "排名"
                  << std::setw(30) << "书名"
                  << std::setw(20) << "作者"
                  << std::setw(10) << "借阅次数" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        int rank = 1;
        for (const auto& pair : sorted_count) {
            if (rank > 10) break;
            std::string book_name = "未知图书", author = "未知作者";
            for (const auto& book : books) {
                if (book.book_id == pair.first) {
                    book_name = book.book_name;
                    author = book.author;
                    break;
                }
            }
            std::cout << std::left << std::setw(5) << rank
                      << std::setw(30) << book_name
                      << std::setw(20) << author
                      << std::setw(10) << pair.second << std::endl;
            rank++;
        }

        if (sorted_count.empty()) std::cout << "\n              暂无借阅记录              " << std::endl;
        else if (sorted_count.size() < 10) std::cout << "\n[提示] 仅" << sorted_count.size() << "本图书有借阅记录" << std::endl;

        std::cout << "========================================" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "[错误] 生成排行榜失败：" << e.what() << std::endl;
    }
}