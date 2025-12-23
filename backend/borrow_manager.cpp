#include "borrow_manager.h"
#include "config.h"
#include "utility.h"
#include "book_manager.h"
#include "reader_manager.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>

// 生成唯一借阅ID（按时间戳+随机数）
std::string generateRecordId() {
    time_t now = time(0);
    return std::to_string(now) + std::to_string(rand() % 1000);
}

// 加载所有借阅记录
std::vector<BorrowRecord> loadAllRecords() {
    std::vector<BorrowRecord> records;
    checkAndCreateFile(RECORDS_PATH);

    std::ifstream file(RECORDS_PATH);
    std::string line;
    getline(file, line); // 跳过表头
    while (getline(file, line)) {
        std::vector<std::string> fields = splitCsvLine(line);
        if (fields.size() == 5) {
            BorrowRecord record;
            record.recordId = fields[0];
            record.bookId = fields[1];
            record.readerId = fields[2];
            record.borrowDate = fields[3];
            record.returnDate = fields[4];
            records.push_back(record);
        }
    }
    file.close();
    return records;
}

// 保存所有借阅记录
void saveAllRecords(const std::vector<BorrowRecord>& records) {
    std::ofstream file(RECORDS_PATH);
    file << "借阅ID,图书ID,读者ID,借阅日期,归还日期" << std::endl;
    for (const auto& record : records) {
        file << record.recordId << ","
            << record.bookId << ","
            << record.readerId << ","
            << record.borrowDate << ","
            << record.returnDate << std::endl;
    }
    file.close();
}

// 图书借阅
void borrowBook() {
    std::vector<Book> books = loadAllBooks();
    std::vector<Reader> readers = loadAllReaders();
    std::vector<BorrowRecord> records = loadAllRecords();

    std::string bookId, readerId;
    std::cout << "===== 图书借阅 =====" << std::endl;
    std::cout << "请输入图书ID：";
    std::cin >> bookId;
    std::cout << "请输入读者ID：";
    std::cin >> readerId;

    // 检查图书是否存在且未借出
    Book* targetBook = nullptr;
    for (auto& book : books) {
        if (book.bookId == bookId) {
            targetBook = &book;
            break;
        }
    }
    if (!targetBook) {
        std::cout << "错误：图书ID不存在！" << std::endl;
        return;
    }
    if (targetBook->isBorrowed) {
        std::cout << "错误：该图书已被借出！" << std::endl;
        return;
    }

    // 检查读者是否存在
    bool readerExist = false;
    for (const auto& reader : readers) {
        if (reader.readerId == readerId) {
            readerExist = true;
            break;
        }
    }
    if (!readerExist) {
        std::cout << "错误：读者ID不存在！" << std::endl;
        return;
    }

    // 生成借阅记录
    BorrowRecord newRecord;
    newRecord.recordId = generateRecordId();
    newRecord.bookId = bookId;
    newRecord.readerId = readerId;
    newRecord.borrowDate = getCurrentDate();
    newRecord.returnDate = ""; // 未归还

    // 更新图书状态 + 保存记录
    targetBook->isBorrowed = true;
    records.push_back(newRecord);
    saveAllBooks(books);
    saveAllRecords(records);

    std::cout << "借阅成功！借阅ID：" << newRecord.recordId << std::endl;
}

// 图书归还
void returnBook() {
    std::vector<Book> books = loadAllBooks();
    std::vector<BorrowRecord> records = loadAllRecords();

    std::string bookId;
    std::cout << "===== 图书归还 =====" << std::endl;
    std::cout << "请输入归还图书ID：";
    std::cin >> bookId;

    // 查找未归还的借阅记录
    BorrowRecord* targetRecord = nullptr;
    for (auto& record : records) {
        if (record.bookId == bookId && record.returnDate.empty()) {
            targetRecord = &record;
            break;
        }
    }
    if (!targetRecord) {
        std::cout << "错误：该图书未被借出，或无借阅记录！" << std::endl;
        return;
    }

    // 更新图书状态 + 归还日期
    for (auto& book : books) {
        if (book.bookId == bookId) {
            book.isBorrowed = false;
            break;
        }
    }
    targetRecord->returnDate = getCurrentDate();

    // 保存数据
    saveAllBooks(books);
    saveAllRecords(records);
    std::cout << "归还成功！归还日期：" << targetRecord->returnDate << std::endl;
}