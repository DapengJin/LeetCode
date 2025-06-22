#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=706 lang=cpp
 *
 * [706] 设计哈希映射
 */

// @lc code=start
class MyHashMap {
    static const int SIZE = 10007; // 一个质数，作为桶数量
    vector<list<pair<int, int>>> buckets;

    int hash(int key) {
        return key % SIZE;
    }

public:
    MyHashMap() : buckets(SIZE) {}

    void put(int key, int value) {
        int idx = hash(key);
        for (auto& [k, v] : buckets[idx]) {
            if (k == key) {
                v = value;
                return;
            }
        }
        buckets[idx].emplace_back(key, value); // 新插入
    }

    int get(int key) {
        int idx = hash(key);
        for (auto& [k, v] : buckets[idx]) {
            if (k == key) return v;
        }
        return -1;
    }

    void remove(int key) {
        int idx = hash(key);
        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it) {
            if (it->first == key) {
                buckets[idx].erase(it);
                return;
            }
        }
    }
};
// @lc code=end

