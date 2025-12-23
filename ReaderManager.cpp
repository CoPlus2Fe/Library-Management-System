#include "ReaderManager.h"
#include "utils.h"
#include "config.h"
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

vector<Reader> ReaderManager::loadAllReadersInternal() {
    vector<Reader> readers;
    checkAndCreateFile(READERS_PATH);

    ifstream file(READERS_PATH);
    if (!file.is_open()) {
        cout << "错误：无法打开读者文件 " << READERS_PATH << endl;
        return readers;
    }

    string line;
    int lineNum = 1;
    getline(file, line); // 跳过表头
    lineNum++;

    while (getline(file, line)) {
        vector<string> fields = splitCsvLine(line);
        if (fields.size() != 4) {
            cout << "警告：读者文件第 " << lineNum << " 行格式错误，跳过" << endl;
            lineNum++;
            continue;
        }

        Reader reader;
        reader.readerId = fields[0];
        reader.name = fields[1];
        try {
            reader.phone = stoi(fields[2]);
        }
        catch (...) {
            cout << "警告：读者文件第 " << lineNum << " 行年龄错误，跳过" << endl;
            lineNum++;
            continue;
        }
        reader.school = fields[3];
        readers.push_back(reader);
        lineNum++;
    }

    file.close();
    cout << "成功加载 " << readers.size() << " 位读者数据" << endl;
    return readers;
}

void ReaderManager::saveAllReadersInternal(const vector<Reader>& readers) {
    ofstream file(READERS_PATH, ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "错误：无法写入读者文件 " << READERS_PATH << endl;
        return;
    }

    file << "读者ID,姓名,联系方式,学院" << endl;
    for (const auto& reader : readers) {
        file << wrapQuotes(reader.readerId) << ","
            << wrapQuotes(reader.name) << ","
            << reader.phone << ","
            << wrapQuotes(reader.school) << endl;
    }

    file.close();
    cout << "成功保存 " << readers.size() << " 位读者数据" << endl;
}

void ReaderManager::addReader() {
    vector<Reader> readers = loadAllReadersInternal();
    Reader newReader;

    cout << "\n===== 新增读者 =====" << endl;
    cout << "请输入读者ID（唯一）：";
    cin >> newReader.readerId;

    // 检查ID重复
    for (const auto& reader : readers) {
        if (reader.readerId == newReader.readerId) {
            cout << "错误：读者ID已存在！" << endl;
            return;
        }
    }

    cin.ignore();
    cout << "请输入姓名：";
    getline(cin, newReader.name);
    cout << "请输入联系方式：";
  
    cin.ignore();
    cout << "请输入学院：";
    getline(cin, newReader.school);
    cin.ignore();
    readers.push_back(newReader);
    saveAllReadersInternal(readers);
    cout << "读者新增成功！" << endl;
}

bool ReaderManager::isReaderExist(const string& readerId) {
    vector<Reader> readers = loadAllReadersInternal();
    for (const auto& reader : readers) {
        if (reader.readerId == readerId) {
            return true;
        }
    }
    return false;
}

vector<Reader> ReaderManager::getAllReaders() {
    return loadAllReadersInternal();
}