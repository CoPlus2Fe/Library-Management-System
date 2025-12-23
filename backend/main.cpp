#include <iostream>
#include "BookManager.h"
#include "ReaderManager.h"
#include "BorrowManager.h"
#include "utils.h"
#include "config.h"

using namespace std;

// 主菜单
void showMainMenu() {
    cout << "\n===== 图书馆管理系统 =====" << endl;
    cout << "1. 图书管理" << endl;
    cout << "2. 读者管理" << endl;
    cout << "3. 借阅管理" << endl;
    cout << "0. 退出系统" << endl;
    cout << "==========================" << endl;
    cout << "请选择功能：";
}

// 图书管理子菜单
void showBookMenu(BookManager& bookMgr) {
    int choice;
    while (true) {
        cout << "\n===== 图书管理子菜单 =====" << endl;
        cout << "1. 新增图书" << endl;
        cout << "2. 查询图书" << endl;
        cout << "3. 展示所有图书" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "请选择：";
        cin >> choice;

        switch (choice) {
        case 1: bookMgr.addBook(); break;
        case 2: bookMgr.queryBook(); break;
        case 3: bookMgr.showAllBooks(); break;
        case 0: return;
        default: cout << "无效选择！" << endl;
        }
        system("pause");
    }
}

// 读者管理子菜单
void showReaderMenu(ReaderManager& readerMgr) {
    int choice;
    while (true) {
        cout << "\n===== 读者管理子菜单 =====" << endl;
        cout << "1. 新增读者" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "请选择：";
        cin >> choice;

        switch (choice) {
        case 1: readerMgr.addReader(); break;
        case 0: return;
        default: cout << "无效选择！" << endl;
        }
        system("pause");
    }
}

// 借阅管理子菜单
void showBorrowMenu(BorrowManager& borrowMgr) {
    int choice;
    while (true) {
        cout << "\n===== 借阅管理子菜单 =====" << endl;
        cout << "1. 图书借阅" << endl;
        cout << "2. 图书归还" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "请选择：";
        cin >> choice;

        switch (choice) {
        case 1: borrowMgr.borrowBook(); break;
        case 2: borrowMgr.returnBook(); break;
        case 0: return;
        default: cout << "无效选择！" << endl;
        }
        system("pause");
    }
}

int main() {
    // 初始化：检查文件夹/文件
    checkAndCreateFolder(DATA_FOLDER);
    checkAndCreateFile(BOOKS_PATH);
    checkAndCreateFile(READERS_PATH);
    checkAndCreateFile(RECORDS_PATH);

    // 初始化管理器
    BookManager bookMgr;
    ReaderManager readerMgr;
    BorrowManager borrowMgr(bookMgr, readerMgr); // 依赖注入

    int mainChoice;
    while (true) {
        showMainMenu();
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: showBookMenu(bookMgr); break;
        case 2: showReaderMenu(readerMgr); break;
        case 3: showBorrowMenu(borrowMgr); break;
        case 0:
            cout << "感谢使用，系统退出！" << endl;
            return 0;
        default:
            cout << "无效选择，请重新输入！" << endl;
        }

        system("pause");
        system("cls"); // 清屏（Windows）
    }
}