#include "bookManager.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

vector<Book> BookManager::loadAllBooksInternal() {
    vector<Book> books;
    checkAndCreateFile(BOOKS_PATH);

    ifstream file(BOOKS_PATH);
    if (!file.is_open()) {
        cout << "错误：无法打开图书文件 " << BOOKS_PATH << endl;
        return books;
    }

    string line;
    int lineNum = 1;
    getline(file, line); // 跳过表头
    lineNum++;

    while (getline(file, line)) {
        vector<string> fields = splitCsvLine(line);
        if (fields.size() != 5) {
            cout << "警告：图书文件第 " << lineNum << " 行格式错误，跳过" << endl;
            lineNum++;
            continue;
        }

        Book book;
        book.bookId = fields[0];
        book.name = fields[1];
        book.author = fields[2];
        book.press = fields[3];
        book.isBorrowed = (fields[4] == "1");
        books.push_back(book);
        lineNum++;
    }

    file.close();
    cout << "成功加载 " << books.size() << " 本图书数据" << endl;
    return books;
}

void BookManager::saveAllBooksInternal(const vector<Book>& books) {
    ofstream file(BOOKS_PATH, ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "错误：无法写入图书文件 " << BOOKS_PATH << endl;
        return;
    }

    file << "图书ID,书名,作者,出版社,是否借出" << endl;
    for (const auto& book : books) {
        file << wrapQuotes(book.bookId) << ","
            << wrapQuotes(book.name) << ","
            << wrapQuotes(book.author) << ","
            << wrapQuotes(book.press) << ","
            << (book.isBorrowed ? "1" : "0") << endl;
    }

    file.close();
    cout << "成功保存 " << books.size() << " 本图书数据" << endl;
}

void BookManager::addBook() {
    vector<Book> books = loadAllBooksInternal();
    Book newBook;

    cout << "\n===== 新增图书 =====" << endl;
    cout << "请输入图书ID（唯一）：";
    cin >> newBook.bookId;

    // 检查ID重复
    for (const auto& book : books) {
        if (book.bookId == newBook.bookId) {
            cout << "错误：图书ID已存在！" << endl;
            return;
        }
    }

    cin.ignore();
    cout << "请输入书名：";
    getline(cin, newBook.name);
    cout << "请输入作者：";
    getline(cin, newBook.author);
    cout << "请输入出版社：";
    getline(cin, newBook.press);
    newBook.isBorrowed = false;

    books.push_back(newBook);
    saveAllBooksInternal(books);
    cout << "图书新增成功！" << endl;
}

void BookManager::queryBook() {
    vector<Book> books = loadAllBooksInternal();
    int choice;
    string keyword;

    cout << "\n===== 查询图书 =====" << endl;
    cout << "1. 按图书ID查询" << endl;
    cout << "2. 按书名查询" << endl;
    cout << "请选择查询方式：";
    cin >> choice;
    cin.ignore();
    cout << "请输入查询关键词：";
    getline(cin, keyword);

    bool found = false;
    cout << "\n===== 查询结果 =====" << endl;
    cout << left << setw(10) << "图书ID"
        << setw(30) << "书名"
        << setw(20) << "作者"
        << setw(25) << "出版社"
        << setw(10) << "是否借出" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    for (const auto& book : books) {
        bool match = (choice == 1 && book.bookId == keyword) ||
            (choice == 2 && book.name.find(keyword) != string::npos);
        if (match) {
            cout << left << setw(10) << book.bookId
                << setw(30) << book.name
                << setw(20) << book.author
                << setw(25) << book.press
                << setw(10) << (book.isBorrowed ? "已借出" : "未借出") << endl;
            found = true;
        }
    }

    if (!found) cout << "未找到匹配的图书！" << endl;
}

void BookManager::showAllBooks() {
    vector<Book> books = loadAllBooksInternal();
    cout << "\n===== 图书馆所有书籍 =====" << endl;

    if (books.empty()) {
        cout << "暂无图书！" << endl;
        return;
    }

    cout << left << setw(10) << "图书ID"
        << setw(30) << "书名"
        << setw(20) << "作者"
        << setw(25) << "出版社"
        << setw(10) << "是否借出" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    for (const auto& book : books) {
        cout << left << setw(10) << book.bookId
            << setw(30) << book.name
            << setw(20) << book.author
            << setw(25) << book.press
            << setw(10) << (book.isBorrowed ? "已借出" : "未借出") << endl;
    }
    cout << "总计：" << books.size() << " 本" << endl;
}

vector<Book> BookManager::getAllBooks() {
    return loadAllBooksInternal(); // 对外暴露加载接口
}

void BookManager::saveAllBooksPublic(const vector<Book>& books) {
    saveAllBooksInternal(books); // 对外暴露保存接口
}

Book BookManager::getBookById(const string& bookId) {
    vector<Book> books = loadAllBooksInternal();
    for (const auto& book : books) {
        if (book.bookId == bookId) {
            return book;
        }
    }
    return Book{}; // 返回空对象
}

bool BookManager::updateBookBorrowStatus(const string& bookId, bool isBorrowed) {
    vector<Book> books = loadAllBooksInternal();
    for (auto& book : books) {
        if (book.bookId == bookId) {
            book.isBorrowed = isBorrowed;
            saveAllBooksInternal(books);
            return true;
        }
    }
    return false;
}