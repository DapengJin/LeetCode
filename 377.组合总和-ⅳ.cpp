#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=377 lang=cpp
 *
 * [377] 组合总和 Ⅳ
 */

// @lc code=start
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<double> dp(target + 1, 0);
        dp[0] = 1;
        int n = nums.size();

        for (int i = 1; i <= target; i++)
            for (auto num : nums )
                if (num <= i)
                    dp[i] += dp[i - num];

        return dp[target];
    }
};
// @lc code=end

