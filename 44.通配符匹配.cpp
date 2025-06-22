#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=44 lang=cpp
 *
 * [44] 通配符匹配
 */

// @lc code=start
class Solution
{
public:
    /**
     *               跳过 '*'         匹配 s[i]
     *            /  dp[i][j - 1] || dp[i - 1][j]  if p[j-1] == '*'
     * dp[i][j] =
     *            \  dp[i - 1][j - 1]              if p[j-1] == '?' || p[j-1] == s[i-1]
     */
    bool isMatch(string s, string p)
    {
        int n = s.size(), m = p.size();

        // dp[i][j] 表示 s 的前 i 个字符能否匹配 p 的前 j 个字符
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        // base case: 空串和空模式可以匹配
        dp[0][0] = true;

        // 初始化：s 是空串时，p 必须全是 '*' 才能匹配
        for (int j = 1; j <= m; j++)
        {
            if (p[j - 1] == '*')
            {
                dp[0][j] = dp[0][j - 1]; // * 可以匹配空串
            }
        }

        // 状态转移
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (p[j - 1] == '*')
                {
                    // 两种情况：
                    // 1. * 匹配空字符 -> 看 dp[i][j-1]
                    // 2. * 匹配 s[i-1] -> 看 dp[i-1][j]
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                }
                else if (p[j - 1] == '?' || s[i - 1] == p[j - 1])
                {
                    // 字符匹配 or ? 通配
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = false;
                }
            }
        }

        return dp[n][m];
    }
};
// @lc code=end
