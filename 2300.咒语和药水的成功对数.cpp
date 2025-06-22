#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2300 lang=cpp
 *
 * [2300] 咒语和药水的成功对数
 */

// @lc code=start
class Solution
{
public:
    vector<int> successfulPairs(vector<int> &spells, vector<int> &potions, long long success)
    {
        int n = spells.size(), m = potions.size();
        vector<int> res;

        ranges::sort(potions); // sort(potions.begin(), potions.end());

        for (auto spell : spells)
        {
            // 因为 spell 是 int， 所以 success % spell 也是 int
            int reminder = success % spell;
            // 因为 success 是 long long， 所以 success / spell 不一定是 int （spell 可能是 1）
            long long target = reminder ? success / spell + 1 : success / spell;

            // 这样写每次二分就只用 int 比较，避免把 potions 中的元素转成 long long 比较
            if (target <= potions.back())
                res.push_back(potions.end() - ranges::lower_bound(potions, (int)target));
            else
                res.push_back(0);
        }

        return res;
    }
};
// @lc code=end
