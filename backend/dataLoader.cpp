#include "dataLoader.h"
#include <fstream>
#include <sstream>

vector<borrowRecord> loadBorrowRecords(const string& filename) {
    vector<borrowRecord> records;
    std::ifstream file(filename);
    string line;

    if (!file.is_open()) {
        return records;
    }

    std::getline(file, line); // 跳过表头

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        string field;
        vector<string> fields;

        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }

        if (fields.size() >= 3) {
            records.emplace_back(fields[1], fields[2]);
        }
    }
    return records;
}
