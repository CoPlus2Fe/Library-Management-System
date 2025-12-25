#ifndef BOOK_BORROW_RANK_H
#define BOOK_BORROW_RANK_H

#include <string>

// 这是你要调用的排行榜函数（声明）
void generateTop10BorrowRank(const std::string& books_csv_path, const std::string& borrow_csv_path);

#endif // BOOK_BORROW_RANK_H