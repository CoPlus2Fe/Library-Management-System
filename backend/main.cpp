#include <iostream>
#include "bookManager.h"
#include "readerManager.h"
#include "borrowManager.h"
#include "utils.h"
#include "config.h"
#include "rank.h"
#include "dataLoader.h"
#include "authManager.h"
#include "./cf/recommender.h"

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
void showReaderMenu(readerManager& readerMgr) {
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
        cout << "3. 图书借阅排行榜" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "请选择：";
        cin >> choice;

        switch (choice) {
        case 1: borrowMgr.borrowBook(); break;
        case 2: borrowMgr.returnBook(); break;
        case 3: generateTop10BorrowRank(BOOKS_PATH, RECORDS_PATH); break;
        case 0: return;
        default: cout << "无效选择！" << endl;
        }
        system("pause");
    }
}

void login(AuthManager& authMgr) {
    // 如果已经登录，询问是否退出
    if (authMgr.isLoggedIn()) {
        cout << "当前已登录用户：" << authMgr.getCurrentUser().username << endl;
        cout << "是否退出登录？(y/n): ";
        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            authMgr.logout();
            cout << "已退出登录。\n";
        } else {
            cout << "继续保持登录状态。\n";
        }
        return;
    }

    //未登录，执行登录流程
    string username, password;
    cout << "===== 用户登录 =====" << endl;
    cout << "用户名: ";
    cin >> username;
    cout << "密码: ";
    cin >> password;

    if (!authMgr.login(username, password)) {
        cout << "登录失败：用户名或密码错误。" << endl;
        return;
    }

    cout << "登录成功，欢迎你：" << username << "！" << endl;
}

void runRecommendation(AuthManager& auth) {
    if (!auth.isLoggedIn()) {
        cout << "请先登录！" << endl;
        return;
    }

    string userId = auth.getCurrentUser().user_id;

    // 1. 加载数据
    vector<borrowRecord> records = loadBorrowRecords(INTER_REEVALUATION_PATH);

    // 2. 创建推荐器
    Recommender recommender;

    // 3. 执行推荐
    vector<string> result = recommender.recommend(userId, records, 5);

    // 4. 输出结果
    cout << "\n📚 推荐给你的书籍：" << endl;
    for (auto& book : result) {
        cout << " - " << book << endl;
    }
}


int main() {
    // 初始化：检查文件夹/文件
    checkAndCreateFolder(DATA_FOLDER);
    checkAndCreateFile(BOOKS_PATH);
    checkAndCreateFile(READERS_PATH);
    checkAndCreateFile(RECORDS_PATH);
    checkAndCreateFile(INTER_REEVALUATION_PATH);

    // 初始化管理器
    BookManager bookMgr;
    readerManager readerMgr;
    BorrowManager borrowMgr(bookMgr, readerMgr); // 依赖注入

    auto users = loadUsers("data/userinfo.csv");
    AuthManager auth(users);
    login(auth);  // 登录

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