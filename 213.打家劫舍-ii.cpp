#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=213 lang=cpp
 *
 * [213] 打家劫舍 II
 */

// @lc code=start
class Solution
{
    int rob198(vector<int> &nums, int start, int end) // [start, end)
    {
        int n = start - end;
        int f0 = 0, f1 = 0;

        for (int i = start; i < end; i++)
        {
            int new_f = max(nums[i] + f0, f1);

            f0 = f1;
            f1 = new_f;
        }

        return f1;
    }

public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();

        return max(nums[0] + rob198(nums, 2, n - 1), // 选 nums[0]  , 就从 2 开始, 最后一个数不可以选
                   rob198(nums, 1, n));              // 不选 nums[0], 就从 1 开始, 最后一个数也可以选
    }
};
// @lc code=end
