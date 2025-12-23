#include "book_manager.h"
#include "reader_manager.h"
#include "borrow_manager.h"
#include <iostream>
#include <cstdlib> // 用于system函数

// 显示主菜单
void showMenu() {
    std::cout << "\n===== 图书馆管理系统 =====" << std::endl;
    std::cout << "1. 图书管理" << std::endl;
    std::cout << "2. 读者管理" << std::endl;
    std::cout << "3. 借阅管理" << std::endl;
    std::cout << "0. 退出系统" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "请选择功能：";
}

// 图书管理子菜单
void bookMenu() {
    int choice;
    std::cout << "\n===== 图书管理子菜单 =====" << std::endl;
    std::cout << "1. 新增图书" << std::endl;
    std::cout << "2. 查询图书" << std::endl;
    std::cout << "3. 展示所有图书" << std::endl;
    std::cout << "0. 返回主菜单" << std::endl;
    std::cout << "请选择：";
    std::cin >> choice;

    switch (choice) {
    case 1: addBook(); break;
    case 2: queryBook(); break;
    case 3: showAllBooks(); break;
    case 0: return;
    default: std::cout << "无效选择！" << std::endl;
    }
}

// 读者管理子菜单
void readerMenu() {
    int choice;
    std::cout << "\n===== 读者管理子菜单 =====" << std::endl;
    std::cout << "1. 新增读者" << std::endl;
    std::cout << "0. 返回主菜单" << std::endl;
    std::cout << "请选择：";
    std::cin >> choice;

    switch (choice) {
    case 1: addReader(); break;
    case 0: return;
    default: std::cout << "无效选择！" << std::endl;
    }
}

// 借阅管理子菜单
void borrowMenu() {
    int choice;
    std::cout << "\n===== 借阅管理子菜单 =====" << std::endl;
    std::cout << "1. 图书借阅" << std::endl;
    std::cout << "2. 图书归还" << std::endl;
    std::cout << "0. 返回主菜单" << std::endl;
    std::cout << "请选择：";
    std::cin >> choice;

    switch (choice) {
    case 1: borrowBook(); break;
    case 2: returnBook(); break;
    case 0: return;
    default: std::cout << "无效选择！" << std::endl;
    }
}

int main() {
    // 初始化：创建数据文件夹（如果不存在）
    system("md D:\\LibrarySystem\\data"); // Windows命令

    int mainChoice;
    while (true) {
        showMenu();
        std::cin >> mainChoice;
        switch (mainChoice) {
        case 1: bookMenu(); break;
        case 2: readerMenu(); break;
        case 3: borrowMenu(); break;
        case 0:
            std::cout << "感谢使用，系统退出！" << std::endl;
            return 0;
        default:
            std::cout << "无效选择，请重新输入！" << std::endl;
        }
        system("pause"); // 暂停查看结果
        system("cls");   // 清屏（Windows）
    }
}