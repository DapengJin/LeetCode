#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1143 lang=cpp
 *
 * [1143] 最长公共子序列
 */

// @lc code=start
class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        string &s = text1, &t = text2;
        int m = s.size(), n = t.size(); 
        /**
         - dfs(i, j) -> 最长 公共子序列 的长度
            - 终止条件 i < 0 || j < 0: return 0;
            - 分类讨论
            s[i] == t[j]: return dfs(i-1, j-1)
            s[i] != t[j]: return max(dfs(i-1, j), dfs(i, j-1))
         */
        function<int(int, int)> dfs = [&](int i, int j) -> int
        {
            if (i < 0 || j < 0)
                return 0;

            if (s[i] == t[j])
                return dfs(i - 1, j - 1);

            return max(dfs(i - 1, j), dfs(i, j - 1));
        };

        return dfs(m - 1, n - 1);        
    }
    // {
    //     int m = text1.size(), n = text2.size();
    //     // vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    //     // for (int i = 0; i < m; i++)
    //     //     for (int j = 0; j < n; j++)
    //     //         dp[i + 1][j + 1] = text1[i] == text2[j] ? dp[i][j] + 1 : max(dp[i + 1][j], dp[i][j + 1]);

    //     // return dp[m][n];

    //     vector<int> dp(n + 1, 0);

    //     // all the i, j for dp need to +1
    //     for (int i = 0; i < m; i++)
    //     {
    //         int pre = dp[0], temp = 0;

    //         for (int j = 0; j < n; j++)
    //         {
    //             temp = dp[j+ 1]; // store the next pre since dp[j + 1] will be overwriting

    //             dp[j + 1] = text1[i] == text2[j] ?
    //                           pre + 1 : // pre is dp[i][j]
    //                           max(dp[j], dp[j + 1]); // dp[j] is dp[i + 1][j] since dp[j] was overwritten
    //                                                  // dp[j + 1] is dp[i][j + 1] since it was not overwritten

    //             pre = temp; // Update `pre` to represent the previous diagonal value for the next iteration
    //         }
    //     }

    //     return dp[n];
    // }
};
// @lc code=end
