#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=713 lang=cpp
 *
 * [713] 乘积小于 K 的子数组
 */

// @lc code=start
class Solution
{
public:
    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        if (k <= 1) return 0;

        int n = nums.size(), res = 0, l = 0, mul = 1;

        for (int r = 0; r < n; r++)
        {
            mul *= nums[r];

            while (l <= r && mul >= k) // !!! "l <= r" 对于 k == 1 需要
                mul /= nums[l++];

            res += r - l + 1; // 以 r 为 右端点 的 子数组 的个数
        }

        return res;
    }
};
// @lc code=end
