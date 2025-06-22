#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */

// @lc code=start
class Solution
{
public:
    /**
     * 为什么我看到这个题目的时候第一反应是要用滑动窗口做？是我哪里理解不到位吗？
     *
     * 有负数不能滑窗，可以做做  560. 和为 K 的子数组
     */
    int maxSubArray(vector<int> &nums)
    {
        /* DP */
        // 定义 f[i] 表示以 nums[i] 结尾的最大子数组和。
        int res = INT_MIN, f = 0, n = nums.size();

        for (auto x : nums)
        {
            // f[i] = max(f[i-1], 0) + nums[i] (如果 f[i-1] 都还没 0 大，就不选前面的了)
            f = max(f, 0) + x;
            res = max(res, f);
        }

        return res;

        /* dfs */
        // function<int(int)> dfs = [&](int i) -> int {
        //     if (i < 0)
        //         return nums[i];

        //     return max(nums[i], dfs(i - 1) + nums[i]);
        // };

        /* prefix sum */
        // // 由于子数组的元素和等于两个前缀和的差，
        // // 所以求出 nums 的前缀和，问题就变成  121. 买卖股票的最佳时机 了。
        // // 本题子数组不能为空，相当于一定要交易一次。
        // int min_p = 0, p = 0, n = nums.size(), res = INT_MIN;

        // for (auto x : nums)
        // {
        //     p += x; // 当前的价格，不可同天交易
        //     res = max(res, p - min_p);
        //     min_p = min(min_p, p); // 买入的最低点
        // }

        // return res;
    }
};
// @lc code=end

