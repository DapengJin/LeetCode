#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=460 lang=cpp
 *
 * [460] LFU 缓存
 */

// @lc code=start
class LFUCache
{
    int capacity;
    using Entry = tuple<int, int, int>; // (key, val, freq)
    using FreqList = list<Entry>;
    using Iter = FreqList::iterator;

    unordered_map<int, FreqList> levels;  // freq -> list of entries
    unordered_map<int, Iter> key_to_iter; // key -> iterator to entry in freq list
    int min_freq = 0;

    void move_forward(Iter iter)
    {
        auto [k, v, f] = *iter;

        // move the node from freq list f to f+1
        // splice 不会改变 iter
        levels[f + 1].splice(levels[f + 1].end(), levels[f], iter);
        get<2>(*iter)++; // increment frequency

        // clean up old freq list if empty
        if (levels[f].empty())
        {
            levels.erase(f);
            if (min_freq == f)
                min_freq++;
        }
    }

public:
    LFUCache(int capacity) : capacity(capacity) {}

    int get(int key)
    {
        if (!key_to_iter.contains(key))
            return -1;

        auto iter = key_to_iter[key];
        int val = get<1>(*iter);

        move_forward(iter);

        return val;
    }

    void put(int key, int value)
    {
        if (capacity == 0)
            return;

        if (key_to_iter.contains(key))
        {
            auto iter = key_to_iter[key];
            get<1>(*iter) = value; // update value
            move_forward(iter);
        }
        else
        {
            // If at capacity, remove least frequently used
            if (key_to_iter.size() == capacity)
            {
                auto &min_lst = levels[min_freq];
                auto [del_key, v, f] = min_lst.front();

                key_to_iter.erase(del_key);
                min_lst.pop_front();

                if (min_lst.empty()) // 不需要手动更新 min_freq，因为你在插入新元素时已经这样做了
                    levels.erase(min_freq);
            }

            // Insert new key with freq = 1
            levels[1].emplace_back(key, value, 1);
            key_to_iter[key] = --levels[1].end();
            min_freq = 1; // reset min freq
        }
    }
};
// @lc code=end
