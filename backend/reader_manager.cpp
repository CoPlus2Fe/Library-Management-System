#include "reader_manager.h"
#include "config.h"
#include "utility.h"
#include <fstream>
#include <iostream>
#include <string>

// 加载所有读者（从CSV读取）
std::vector<Reader> loadAllReaders() {
    std::vector<Reader> readers;
    checkAndCreateFile(READERS_PATH);

    std::ifstream file(READERS_PATH);
    std::string line;
    getline(file, line); // 跳过表头
    while (getline(file, line)) {
        std::vector<std::string> fields = splitCsvLine(line);
        if (fields.size() == 4) {
            Reader reader;
            reader.readerId = fields[0];
            reader.name = fields[1];
            reader.age = stoi(fields[2]);
            reader.phone = fields[3];
            readers.push_back(reader);
        }
    }
    file.close();
    return readers;
}

// 保存所有读者（写入CSV）
void saveAllReaders(const std::vector<Reader>& readers) {
    std::ofstream file(READERS_PATH);
    file << "读者ID,姓名,年龄,联系方式" << std::endl;
    for (const auto& reader : readers) {
        file << reader.readerId << ","
            << reader.name << ","
            << reader.age << ","
            << reader.phone << std::endl;
    }
    file.close();
}

// 新增读者
void addReader() {
    std::vector<Reader> readers = loadAllReaders();
    Reader newReader;

    std::cout << "===== 新增读者 =====" << std::endl;
    std::cout << "请输入读者ID（唯一）：";
    std::cin >> newReader.readerId;

    // 检查ID重复
    for (const auto& reader : readers) {
        if (reader.readerId == newReader.readerId) {
            std::cout << "错误：读者ID已存在！" << std::endl;
            return;
        }
    }

    std::cin.ignore();
    std::cout << "请输入姓名：";
    std::getline(std::cin, newReader.name);
    std::cout << "请输入年龄：";
    std::cin >> newReader.age;
    std::cin.ignore();
    std::cout << "请输入联系方式：";
    std::getline(std::cin, newReader.phone);

    readers.push_back(newReader);
    saveAllReaders(readers);
    std::cout << "读者新增成功！" << std::endl;
}