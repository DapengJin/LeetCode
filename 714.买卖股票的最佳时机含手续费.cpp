#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=714 lang=cpp
 *
 * [714] 买卖股票的最佳时机含手续费
 */

// @lc code=start
class Solution
{
public:
    int maxProfit(vector<int> &prices, int fee)
    {
        // f0, f1 = 0, -inf
        // for p in prices:
        //     f0, f1 = max(f0, f1 + p - fee), max(f1, f0 - p)
        // return f0

        int n = prices.size(), hold = 1;
        vector dp(n + 1, vector<int>(2, INT_MIN / 2));
        dp[0][!hold] = 0;

        for (int i = 0; i < n; i++)
        {
            dp[i + 1][hold]  = max(dp[i][hold], dp[i][!hold] - prices[i] - fee);
            dp[i + 1][!hold] = max(dp[i][!hold], dp[i][hold] + prices[i]);
        }

        return dp[n][!hold];
    }
};
// @lc code=end
