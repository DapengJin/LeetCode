#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 */

// @lc code=start
class Solution
{
public:
    int minDistance(string s, string t)
    {
        // int m = s.size(), n = t.size();
        // vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        // for (int j = 0; j <= n; j++)
        //     dp[0][j] = j;

        // for (int i = 0; i < m; i++)
        // {
        //     dp[i + 1][0] = i + 1; // !!! [i + 1] not [i]

        //     for (int j = 0; j < n; j++)
        //     {
        //         if (s[i] == t[j])
        //             dp[i + 1][j + 1] = dp[i][j];
        //         else
        //             dp[i + 1][j + 1] = min(min(dp[i][j + 1], dp[i + 1][j]), dp[i][j]) + 1;
        //     }
        // }

        // return dp[m][n];

        /* 空间优化 O(n) */
        int m = s.size(), n = t.size();
        vector<int> dp(n + 1);

        iota(dp.begin(), dp.end(), 0);

        for (int i = 0; i < m; i++)
        {
            int pre = dp[0]; // !!! 之前没有

            dp[0] = i + 1;

            for (int j = 0; j < n; j++)
            {
                int temp = dp[j + 1];

                if (s[i] == t[j])
                    dp[j + 1] = pre; // !!! dp[i][j] 全部替换成 pre
                else
                    dp[j + 1] = min(min(dp[j + 1], dp[j]), pre) + 1;
                
                pre = temp;
            }
        }

        return dp[n];

        // n, m = len(s), len(t)
        // @cache  # 缓存装饰器，避免重复计算 dfs 的结果（记忆化）
        // def dfs(i: int, j: int) -> int:
        //     if i < 0:
        //         return j + 1
        //     if j < 0:
        //         return i + 1
        //     if s[i] == t[j]:
        //         return dfs(i - 1, j - 1)
        //     return min(dfs(i - 1, j), dfs(i, j - 1), dfs(i - 1, j - 1)) + 1
        // return dfs(n - 1, m - 1)
    }
};
// @lc code=end
