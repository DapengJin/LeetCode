#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=322 lang=cpp
 *
 * [322] 零钱兑换
 */

// @lc code=start
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int m = coins.size();
        // vector<vector<int>> dp(m + 1, vector<int>(amount + 1, INT_MAX / 2));

        // // dp[0][0] 表示 没有硬币可选，需要找零 0 元的时候，需要硬币的个数
        // dp[0][0] = 0;

        // for (int i = 0; i < m; i++)
        //     for (int j = 0; j <= amount; j++)
        //     {
        //         dp[i + 1][j] = dp[i][j]; // 跳过 coins[i]

        //         if (j >= coins[i]) // 选 coins[i]
        //             dp[i + 1][j] = min(dp[i + 1][j], dp[i + 1][j - coins[i]] + 1);
        //     }

        // int ans = dp[m][amount];

        // return ans < INT_MAX / 2 ? ans : -1;

        /* 空间优化 O(amount) */
        vector<int> dp(amount + 1, INT_MAX / 2);

        dp[0] = 0;

        for (auto coin : coins)
            for (int j = coin; j <= amount; j++) // 如果 j < coin 就没必要更新，因为不选的情况下就是 dp[j] = dp[j]
                dp[j] = min(dp[j],               // 不选
                            dp[j - coin] + 1);   // 选

        int ans = dp[amount];

        return ans < INT_MAX / 2 ? ans : -1;

        // @cache  # 缓存装饰器，避免重复计算 dfs 的结果（记忆化）
        // def dfs(i: int, c: int) -> int:
        //     if i < 0:
        //         return 0 if c == 0 else inf
        //     if c < coins[i]:
        //         return dfs(i - 1, c)
        //     return min(dfs(i - 1, c), dfs(i, c - coins[i]) + 1)
        // ans = dfs(len(coins) - 1, amount)
        // return ans if ans < inf else -1
    }
};
// @lc code=end
