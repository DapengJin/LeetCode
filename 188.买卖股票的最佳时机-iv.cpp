#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=188 lang=cpp
 *
 * [188] 买卖股票的最佳时机 IV
 */

// @lc code=start
class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        // int n = prices.size();
        // // k + 2 是因为 0 到 k 是 k+1个数，然后 j-1 需要给 j 整体 +1
        // vector f(n + 1, vector<vector<int>>(k + 2, vector<int>(2, INT_MIN / 2)));

        // for (int j = 0; j < k + 1; j++)
        //     f[0][j + 1][0] = 0; // !!! 初始化的时候也记得 +1, j == -1 的时候return -inf

        // for (int i = 0; i < n; i++)
        //     for (int j = 0; j < k + 1; j++)
        //     {
        //         f[i + 1][j + 1][1] = max(f[i][j + 1][1], f[i][j][0]     - prices[i]);
        //         f[i + 1][j + 1][0] = max(f[i][j + 1][0], f[i][j + 1][1] + prices[i]);
        //     }

        // return f[n][k + 1][0];

        /* 空间优化：
         * 因为 f[i+1][j] 都是从 f[i][j] 转移过来的
         * 所以 这里和 0-1 背包类似 需要写一个倒叙遍历
         * 
         * 修改：
         * 1. 删除 i 的 dimension
         * 2. 改 j 为倒叙
         */
        int n = prices.size();
        // k + 2 是因为 0 到 k 是 k+1个数，然后 j-1 需要给 j 整体 +1
        vector f(k + 2, vector<int>(2, INT_MIN / 2));

        for (int j = 0; j < k + 1; j++)
            f[j + 1][0] = 0; // !!! 初始化的时候也记得 +1, j == -1 的时候return -inf

        for (int i = 0; i < n; i++)
            for (int j = k; j >= 0; j--)
            {
                f[j + 1][1] = max(f[j + 1][1], f[j][0]     - prices[i]);
                f[j + 1][0] = max(f[j + 1][0], f[j + 1][1] + prices[i]);
            }

        return f[k + 1][0];
        

        // n = len(prices)
        // # copied from 122
        // @cache  # 缓存装饰器，避免重复计算 dfs 的结果
        // def dfs(i: int, j: int, hold: bool) -> int:  # since we have i - 1 and i < 0, i should +1 for dp
        //     if j < 0:
        //         return -inf                          # dp[*][j][*] = -inf，j 不能为负
        //     if i < 0:
        //         return -inf if hold else 0           # dp[0][j][1] = -inf，第 0 天不可能持有股票
        //                                              # dp[0][j][0] = 0   ，第 0 天开始未持有股票，利润为 0
        //     if hold:
        //         return max(dfs(i - 1, j, True), dfs(i - 1, j-1, False) - prices[i])
        //     return max(dfs(i - 1, j, False), dfs(i - 1, j, True) + prices[i])
        // return dfs(n - 1, k, False)
    }
};
// @lc code=end
