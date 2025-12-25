#include "recommender.h"
#include <unordered_map>
#include <algorithm>

// -----------------------------
// 加权 Jaccard 相似度
// a / b: book_id -> weight
// -----------------------------
static double weightedJaccard(
    const std::unordered_map<string, int>& a,
    const std::unordered_map<string, int>& b
) {
    double numerator = 0.0;
    double denominator = 0.0;

    // 遍历 a
    for (const auto& pairA : a) {
        const string& book = pairA.first;
        int wa = pairA.second;

        auto it = b.find(book);
        if (it != b.end()) {
            int wb = it->second;
            numerator += std::min(wa, wb);
            denominator += std::max(wa, wb);
        } else {
            denominator += wa;
        }
    }

    // b 中有、a 中没有的
    for (const auto& pairB : b) {
        if (a.find(pairB.first) == a.end()) {
            denominator += pairB.second;
        }
    }

    if (denominator == 0.0) return 0.0;
    return numerator / denominator;
}

//推荐算法实现
vector<string> Recommender::recommend(
    const string& user_id,
    const vector<borrowRecord>& records,
    int topN
) {
    // 1. 构建 user -> (book -> weight)
    std::unordered_map<
        string,
        std::unordered_map<string, int>
    > userBookWeights;

    for (const auto& r : records) {
        int weight = 1 + r.renewCount;  // 权重定义
        userBookWeights[r.user_id][r.book_id] += weight;
    }

    // 用户不存在
    if (userBookWeights.find(user_id) == userBookWeights.end()) {
        return {};
    }

    const auto& targetBooks = userBookWeights[user_id]; 
    // 2. 计算相似用户
    std::vector<std::pair<string, double>> similarities;

    for (const auto& pair : userBookWeights) {
        const string& otherUser = pair.first;
                if (otherUser == user_id) continue;

        double sim = weightedJaccard(
            targetBooks,
            pair.second
        );

        if (sim > 0.0) {
            similarities.push_back({otherUser, sim});
        }
    }

    if (similarities.empty()) {
        return {};
    }

    // 3. 按相似度排序
    std::sort(similarities.begin(), similarities.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        }
    );

    // 4. 取 Top-K 相似用户
    int K = std::min(5, (int)similarities.size());

    // 5. 候选书打分
    std::unordered_map<string, double> bookScore;

    for (int i = 0; i < K; ++i) {
        const string& simUser = similarities[i].first;
        double simScore = similarities[i].second;

        for (const auto& pair : userBookWeights[simUser]) {
            const string& bookId = pair.first;

            // 已借过的不推荐
            if (targetBooks.find(bookId) != targetBooks.end()) continue;

            bookScore[bookId] += simScore;
        }
    }

    // 6. 排序取 Top-N
    std::vector<std::pair<string, double>> sortedBooks(
        bookScore.begin(), bookScore.end()
    );

    std::sort(sortedBooks.begin(), sortedBooks.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        }
    );

    vector<string> result;
    for (int i = 0; i < (int)sortedBooks.size() && i < topN; ++i) {
        result.push_back(sortedBooks[i].first);
    }

    return result;
}
