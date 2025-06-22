#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1011 lang=cpp
 *
 * [1011] 在 D 天内送达包裹的能力
 */

// @lc code=start
class Solution
{
public:
    int shipWithinDays(vector<int> &nums, int k)
    {
        int n = nums.size();

        auto check = [&](int cap)
        {
            int day = 1; // # segments
            int load = 0;

            for (auto num : nums)
            {
                if (num > cap)
                    return false;

                load += num; // 装货

                if (load > cap) // 装不下 -> 开启新一天
                {
                    day++;
                    load = num;
                }

                if (day > k)
                    return false;
            }

            return true;
        };

        /**
         *         不满足           可能的答案区间              满足
         *    |------------|---------------------------|-----------|
         *  l = max-1     max(nums)            ...   sum(nums)    r=sum+1
         *  check=false                                           check=true
         */
        // res range [max(nums) 最重的那个要能装上船, sum(nums) 一次运完所有的货]
        int l = ranges::max(nums) - 1;
        // right side satisfies the check
        int r = accumulate(nums.begin(), nums.end(), 0) + 1;

        while (l + 1 < r)
        {
            int mid = l - (l - r) / 2;

            if (check(mid))
                r = mid;
            else
                l = mid;
        }

        return r;
    }
};
// @lc code=end
