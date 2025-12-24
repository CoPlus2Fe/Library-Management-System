//推荐系统的头文件，定义了一个Recommender类，用于生成基于用户协同过滤的推荐

#pragma once        //避免同一个头文件被多次包含（include），比#ifndef好，因为它不需要定义唯一的宏名
#include <string>         //引入 C++ 字符串库
#include <vector>      //动态数组，可以自动扩容
#include <utility>       //引入 std::pair，用于存储成对的数据（uesr_id, book_id），pair是将2个数据组合成一组数据， pair的实现是一个结构体

//简写命名空间
using std::string;  
using std::vector;

//类型别名borrowRecord，表示借阅记录，记录user_id和book_id，borrowRecord.first=user_id，borrowRecord.second=book_id
using borrowRecord = std::pair<string, string>;

/// @brief 定义一个类，在.cpp文件中实现推荐算法的功能
class Recommender {
public:     //全局可见的函数
    /**
     * @brief 基于用户协同过滤生成推荐
     * @param userId 目标用户 ID
     * @param records 所有借阅记录 (user_id, book_id)
     * @param topN 推荐数量
     * @return 推荐的 book_id 列表
     */
    vector<string> recommend(const string& userId,
                             const vector<borrowRecord>& records,
                             int topN = 10);
};
/* 
vector是向量类型，它可以容纳许多类型的数据，如若干个整数，所以称其为容器
const：不变的量
string&引用userId减少内存开销
vector<BorrowRecord>& records：传入所有用户的借阅记录，用vector容器存储,每个借阅记录是一个BorrowRecord类型的pair
*/
