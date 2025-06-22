#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=494 lang=cpp
 *
 * [494] 目标和
 */

// @lc code=start
class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {
        /* assume 正数和是 p
         *        总和是   s
         *
         * then   负数和是 s-p （不带符号）
         *        p - (s-p) = target
         *        p = (s+target)/2 (必须整除)
         *
         * 问题转化为 选 nums 里面其中的一些数，使得它们相加等于 p
         *
         * dp[i][j] 表示 当容量为 j 时，从前 i 个物品中得到的最大价值和
         *
         * dp[i][j] = dp[i-1][j] （不选）+
         *            dp[i-1][j-nums[i]] (当 j-nums[i] >= 0，可以选)
         *
         * dp[i][0]
         */
        target = target + accumulate(nums.begin(), nums.end(), 0);

        if (target % 2 || target < 0)
            return 0;

        target = target / 2;

        int n = nums.size();
        // vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));

        // dp[0][0] = 1; // j needs to be exactly 0

        // for (int i = 0; i < n; i++)
        //     for (int j = 0; j <= target; j++)
        //         if (j - nums[i] < 0) // 不选
        //             dp[i + 1][j] = dp[i][j];
        //         else // 选
        //             dp[i + 1][j] = dp[i][j] + dp[i][j - nums[i]];

        // return dp[n][target];

        vector<int> dp(target + 1, 0); // 如果条件改为：至多为 target，那么全部初始化成 1，因为 dfs(-1,c) 都是 1

        dp[0] = 1; // j needs to be exactly 0

        for (auto num : nums)
            // only update the dp[j] that j >= num, keep others unchanged
            for (int j = target; j >= num; j--) 
                // if (j - num < 0) // 不选
                //     dp[j] = dp[j];
                // else // 选
                dp[j] = dp[j] + dp[j - num];

        return dp[target];

        // @cache
        // def dfs(i, c):
        //     if i < 0:
        //         return 1 if c == 0 else 0 // 如果条件改为：至多为 target，那么就直接 return 1 （c 一定 >= 0）
        //     if c < nums[i]:               // 如果条件改为：至少为 target，那么就 return 1 if c <= 0 else 0
        //         return dfs(i-1,c)         //     这也不需要
        //     return dfs(i-1,c) + dfs(i-1, c-nums[i])
        // return dfs(n-1, target)
    }
};
// @lc code=end
