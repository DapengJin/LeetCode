#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=209 lang=cpp
 *
 * [209] 长度最小的子数组
 */

// @lc code=start
class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int n = nums.size(), res = INT_MAX, l = 0, s = 0;

        for (int r = 0; r < n; r++)
        {
            s += nums[r];

            while (s >= target) // 满足条件
            {
                res = min(res, r - l + 1); // 记录结果
                s -= nums[l++];            // 收缩窗口直到 sum < k
            }
        }

        return res == INT_MAX ? 0 : res;
    }
};
// @lc code=end
