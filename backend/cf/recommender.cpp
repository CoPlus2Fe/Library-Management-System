#include "recommender.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

// ------------------------
// 工具函数：Jaccard 相似度
// ------------------------
static double jaccard(const std::unordered_set<string>& a,
                      const std::unordered_set<string>& b) {
    if (a.empty() || b.empty()) return 0.0;

    int intersection = 0;
    for (const auto& x : a) {
        if (b.count(x)) intersection++;
    }

    int unionCount = a.size() + b.size() - intersection;
    return unionCount == 0 ? 0.0 : (double)intersection / unionCount;
}

// ------------------------
// 核心推荐实现
// ------------------------
vector<string> Recommender::recommend(const string& userId,
                                      const vector<BorrowRecord>& records,
                                      int topN) {
    // 1. 构建 user -> books 映射
    std::unordered_map<string, std::unordered_set<string>> userBooks;

    for (const auto& r : records) {
        userBooks[r.first].insert(r.second);
    }

    // 如果用户不存在或无历史，直接返回空
    if (!userBooks.count(userId)) {
        return {};
    }

    const auto& targetBooks = userBooks[userId];

    // 2. 计算与其他用户的相似度
    std::vector<std::pair<string, double>> similarities;

    for (const auto& [otherUser, books] : userBooks) {
        if (otherUser == userId) continue;

        double sim = jaccard(targetBooks, books);
        if (sim > 0) {
            similarities.emplace_back(otherUser, sim);
        }
    }

    // 没有相似用户
    if (similarities.empty()) {
        return {};
    }

    // 3. 按相似度排序（降序）
    std::sort(similarities.begin(), similarities.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    // 4. 选 Top-K 相似用户（这里 K=5）
    int K = std::min(5, (int)similarities.size());

    // 5. 候选书打分
    std::unordered_map<string, double> bookScore;

    for (int i = 0; i < K; ++i) {
        const auto& simUser = similarities[i].first;
        double simScore = similarities[i].second;

        for (const auto& bookId : userBooks[simUser]) {
            // 目标用户已经借过的书不推荐
            if (targetBooks.count(bookId)) continue;

            bookScore[bookId] += simScore;
        }
    }

    // 6. 排序得到 Top-N 推荐
    std::vector<std::pair<string, double>> sortedBooks(
        bookScore.begin(), bookScore.end());

    std::sort(sortedBooks.begin(), sortedBooks.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    vector<string> result;
    for (int i = 0; i < sortedBooks.size() && i < topN; ++i) {
        result.push_back(sortedBooks[i].first);
    }

    return result;
}
