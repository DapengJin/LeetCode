#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=705 lang=cpp
 *
 * [705] 设计哈希集合
 */

// @lc code=start
class MyHashSet
{
    const int SIZE = 10007;
    vector<list<int>> buckets;

    int hash(int key)
    {
        return key % SIZE;
    }

public:
    MyHashSet() : buckets(SIZE) {}

    void add(int key)
    {
        if (!contains(key))
            buckets[hash(key)].push_back(key);
    }

    void remove(int key)
    {
        int idx = hash(key);

        for (auto iter = buckets[idx].begin(); iter != buckets[idx].end(); ++iter)
            if (*iter == key)
            {
                buckets[idx].erase(iter);
                return;
            }
    }

    bool contains(int key)
    {
        int idx = hash(key);

        for (auto k: buckets[idx])
            if (k == key)
                return true;

        return false;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
// @lc code=end
