#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=122 lang=cpp
 *
 * [122] 买卖股票的最佳时机 II
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // int n = prices.size(); 
        // vector<vector<int>> dp(n+1, vector<int>(2));

        // dp[0][1] = INT_MIN; 

        // for (int i = 0; i < n; i++)
        // {
        //     dp[i+1][0] = max(dp[i][0], dp[i][1] + prices[i]); 
        //     dp[i+1][1] = max(dp[i][1], dp[i][0] - prices[i]);
        // }

        // return dp[n][0];

        int n = prices.size(), f0 = 0, f1 = INT_MIN;

        for (auto price: prices)
        {
            int new_f0 = max(f0, f1 + price); 
            f1 = max(f1, f0 - price); 
            f0 = new_f0; 
        }

        return f0; 

        // n = len(prices)
        // @cache  # 缓存装饰器，避免重复计算 dfs 的结果
        // def dfs(i: int, hold: bool) -> int: # since we have i - 1 and i < 0, i should +1 for dp
        //     if i < 0:
        //         return -inf if hold else 0  # dp[0][1] = -inf 
        //                                     # dp[0][0] = 0
        //     if hold:
        //         return max(dfs(i - 1, True), dfs(i - 1, False) - prices[i])
        //     return max(dfs(i - 1, False), dfs(i - 1, True) + prices[i])
        // return dfs(n - 1, False)
    }
};
// @lc code=end

