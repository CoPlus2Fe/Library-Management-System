#include "borrowManager.h"
#include "utils.h"
#include "config.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<borrowRecord> BorrowManager::loadAllRecordsInternal() {
    vector<borrowRecord> records;
    checkAndCreateFile(RECORDS_PATH);

    ifstream file(RECORDS_PATH);
    if (!file.is_open()) {
        cout << "错误：无法打开借阅记录文件 " << RECORDS_PATH << endl;
        return records;
    }

    string line;
    int lineNum = 1;
    getline(file, line); // 跳过表头
    lineNum++;

    while (getline(file, line)) {
        vector<string> fields = splitCsvLine(line);
        if (fields.size() != 5) {
            cout << "警告：借阅记录文件第 " << lineNum << " 行格式错误，跳过" << endl;
            lineNum++;
            continue;
        }

        borrowRecord record;
        record.recordId = fields[0];
        record.book_id = fields[1];
        record.user_id = fields[2];
        record.borrowDate = fields[3];
        record.returnDate = fields[4];
        records.push_back(record);
        lineNum++;
    }

    file.close();
    cout << "成功加载 " << records.size() << " 条借阅记录" << endl;
    return records;
}

void BorrowManager::saveAllRecordsInternal(const vector<borrowRecord>& records) {
    ofstream file(RECORDS_PATH, ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "错误：无法写入借阅记录文件 " << RECORDS_PATH << endl;
        return;
    }

    file << "借阅ID,图书ID,读者ID,借阅日期,归还日期" << endl;
    for (const auto& record : records) {
        file << wrapQuotes(record.recordId) << ","
             << wrapQuotes(record.book_id) << ","
             << wrapQuotes(record.user_id) << ","
             << wrapQuotes(record.borrowDate) << ","
             << wrapQuotes(record.returnDate) << endl;
    }

    file.close();
    cout << "成功保存 " << records.size() << " 条借阅记录" << endl;
}

string BorrowManager::generateRecordId() {
    srand((unsigned int)time(0));
    time_t now = time(0);
    return to_string(now) + to_string(rand() % 1000);
}

void BorrowManager::borrowBook() {
    vector<Book> books = bookMgr.getAllBooks(); // 调用公有接口（解决C2248）
    string bookId, readerId;

    cout << "\n===== 图书借阅 =====" << endl;
    cout << "请输入图书ID：";
    cin >> bookId;
    cout << "请输入读者ID：";
    cin >> readerId;

    // 检查图书
    Book targetBook = bookMgr.getBookById(bookId);
    if (targetBook.bookId.empty()) {
        cout << "错误：图书ID不存在！" << endl;
        return;
    }
    if (!targetBook.isBorrowed) {
        cout << "错误：该图书已借出！" << endl;
        return;
    }

    // 检查读者（解决VCR001）
    if (!readerMgr.isReaderExist(readerId)) {
        cout << "错误：读者ID不存在！" << endl;
        return;
    }

    // 创建借阅记录
    vector<borrowRecord> records = loadAllRecordsInternal();
    borrowRecord newRecord;
    newRecord.recordId = generateRecordId();
    newRecord.book_id = bookId;
    newRecord.user_id = readerId;
    newRecord.borrowDate = getCurrentDate();
    newRecord.returnDate = "";

    // 更新图书状态
    bookMgr.updateBookBorrowStatus(bookId, true);
    records.push_back(newRecord);
    saveAllRecordsInternal(records);

    cout << "借阅成功！借阅ID：" << newRecord.recordId << endl;
}

void BorrowManager::returnBook() {
    vector<Book> books = bookMgr.getAllBooks();
    vector<borrowRecord> records = loadAllRecordsInternal();
    string bookId;

    cout << "\n===== 图书归还 =====" << endl;
    cout << "请输入归还图书ID：";
    cin >> bookId;

    // 查找未归还记录
    borrowRecord* targetRecord = nullptr;
    for (auto& record : records) {
        if (record.book_id == bookId && record.returnDate.empty()) {
            targetRecord = &record;
            break;
        }
    }
    if (!targetRecord) {
        cout << "错误：该图书未借出！" << endl;
        return;
    }

    // 更新状态
    bookMgr.updateBookBorrowStatus(bookId, false);
    targetRecord->returnDate = getCurrentDate();
    saveAllRecordsInternal(records);

    cout << "归还成功！归还日期：" << targetRecord->returnDate << endl;
}