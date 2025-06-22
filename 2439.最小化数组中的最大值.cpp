#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2439 lang=cpp
 *
 * [2439] 最小化数组中的最大值
 */

// @lc code=start
class Solution
{
public:
    int minimizeArrayValue(vector<int> &nums)
    {
        int n_max = ranges::max(nums);
        int n = nums.size();
        // res 范围 [0, n_max]
        // 单调性 n_max - 1 成立， n_max 也成立
        auto check = [&](int limit) -> bool
        {
            long long extra = 0;
            for (int i = nums.size() - 1; i > 0; i--)
            {
                extra = max(nums[i] + extra - limit, 0LL);
            }
            return nums[0] + extra <= limit;
        };
        // auto check = [&](int mid) -> bool
        // {
        //     long long num = nums[n - 1];

        //     for (int i = n - 1; i >= 1; i--)
        //     {
        //         if (num > mid)
        //             num = nums[i - 1] + (num - mid);
        //         else
        //             num = nums[i - 1];
        //     }

        //     if (num > mid)
        //         return false;

        //     return true;
        // };

        int l = -1, r = n_max + 1;

        while (l + 1 < r)
        {
            int mid = l + (r - l) / 2;
            (check(mid) ? r : l) = mid;
        }

        return r;
    }
};
// @lc code=end
