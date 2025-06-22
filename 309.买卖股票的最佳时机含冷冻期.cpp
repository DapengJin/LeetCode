#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=309 lang=cpp
 *
 * [309] 买卖股票的最佳时机含冷冻期
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {

        /* 所有一维标号再加1 */
        int n = prices.size();
        vector<array<int, 2>> f(n + 2);
        f[1][1] = INT_MIN;
        for (int i = 0; i < n; i++) {
            f[i + 2][0] = max(f[i + 1][0], f[i + 1][1] + prices[i]);
            f[i + 2][1] = max(f[i + 1][1], f[i][0] - prices[i]);
        }
        return f[n + 1][0];

        // int n = prices.size(); 
        // vector<vector<int>> dp(n+1, vector<int>(2));

        // dp[0][1] = INT_MIN; 

        // for (int i = 0; i < n; i++)
        // {
        //     dp[i+1][0] = max(dp[i][0], dp[i][1] + prices[i]); 
        //     dp[i+1][1] = max(dp[i][1], i-1 >= 0 ? dp[i-1][0] - prices[i] : - prices[i]);
        // }

        // return dp[n][0];
    }
};
// @lc code=end

