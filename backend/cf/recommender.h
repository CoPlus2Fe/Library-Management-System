// backend/cf/recommender.h
#pragma once
#include <string>
#include <vector>
#include <utility>

using std::string;
using std::vector;

// 借阅记录：<user_id, book_id>
using BorrowRecord = std::pair<string, string>;

class Recommender {
public:
    /**
     * @brief 基于用户协同过滤生成推荐
     * @param userId 目标用户 ID
     * @param records 所有借阅记录 (user_id, book_id)
     * @param topN 推荐数量
     * @return 推荐的 book_id 列表
     */
    vector<string> recommend(const string& userId,
                             const vector<BorrowRecord>& records,
                             int topN = 10);
};
