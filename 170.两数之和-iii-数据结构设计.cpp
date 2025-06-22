#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=170 lang=cpp
 *
 * [170] 两数之和 III - 数据结构设计
 */

// @lc code=start
class TwoSum
{
    unordered_map<int, int> counter;

public:
    TwoSum() {}

    void add(int number)
    {
        counter[number]++;
    }

    bool find(int value)
    {

        for (auto [y, freq] : counter)
        {
            long long x = (long long) value - y;

            if (counter.contains(x))
            {
                if (x == y && counter[x] < 2)
                    continue;

                return true;
            }
        }

        return false;
    }
};
// @lc code=end
