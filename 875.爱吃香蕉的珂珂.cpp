#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=875 lang=cpp
 *
 * [875] 爱吃香蕉的珂珂
 */

// @lc code=start
class Solution
{
public:
    int minEatingSpeed(vector<int> &piles, int h)
    {

        // piles.length <= h，香蕉不可能有吃不完的情况
        int n = piles.size(), pile_max = 0;

        for (auto pile : piles)
            pile_max = max(pile_max, pile);

        // 结果范围就是 [1, pile_max]
        int l = 0, r = pile_max + 1; // r 的右边表示在 h 小时内（含）可以吃完所有香蕉

        while (l + 1 < r)
        {
            int mid = l + (r - l) / 2;
            int hours = n; // 每个 pile 至少都要 1 hour

            for (auto pile : piles)
            {
                hours += (pile - 1) / mid; // 向上取整了

                if (hours > h) break; 
            }
                
            if (hours <= h)
                r = mid;
            else
                l = mid;
        }

        return r; 
    }
};
// @lc code=end
