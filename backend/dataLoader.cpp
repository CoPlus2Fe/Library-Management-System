#include "dataLoader.h"
#include <fstream>
#include <sstream>
#include "./dataStructs.h"

using std::vector;
using std::string;

vector<borrowRecord> loadBorrowRecords(const string& filename) {
    vector<borrowRecord> records;
    std::ifstream file(filename);
    string line;

    if (!file.is_open()) {
        return records;
    }

    // 跳过表头
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        string field;
        vector<string> fields;

        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }

        // CSV 至少要有7个值
        if (fields.size() < 7) continue;

        borrowRecord r;
        r.user_id = fields[1];
        r.book_id = fields[2];

        // 续借次数，空则视为 0
        if (fields[6].empty()) {
            r.renewCount = 0;
        } else {
            r.renewCount = std::stoi(fields[6]);
        }

        records.push_back(r);
    }

    return records;
}

std::vector<User> loadUsers(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) return users;

    std::getline(file, line); // 跳过表头

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        User u;

        std::getline(ss, field, ',');
        u.user_id = std::stoi(field);

        std::getline(ss, u.username, ',');
        std::getline(ss, u.password, ',');

        users.push_back(u);
    }
    return users;
}
