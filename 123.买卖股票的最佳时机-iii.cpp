#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=123 lang=cpp
 *
 * [123] 买卖股票的最佳时机 III
 */

// @lc code=start
class Solution {
public:
    // 本题相当于 188. 买卖股票的最佳时机 IV 的 k=2 的情况，做法是完全一样的
    int maxProfit(vector<int>& prices) {
        int n = prices.size(), hold = 1; 
        // j 是 至多的交易次数，j = 0, 1, 2, 
        // however，状态转移方程有个 j-1，所以我们要 j 整体 +1（state transition equation）
        vector f(n+1, vector<vector<int>>(4, vector<int>(2, INT_MIN/2))); 

        for (int j = 0; j <= 2; j++)
            f[0][j+1][0] = 0;
        
        for (int i = 0; i < n; i++)
            for (int j =0 ; j <= 2; j++)
            { 
                f[i+1][j+1][hold]  = max(f[i][j+1][hold],  f[i][j][!hold] - prices[i]);
                f[i+1][j+1][!hold] = max(f[i][j+1][!hold], f[i][j+1][hold]  + prices[i]);
            }

        return f[n][3][0];
    }
};
// @lc code=end

