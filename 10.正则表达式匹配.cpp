#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=10 lang=cpp
 *
 * [10] 正则表达式匹配
 */

// @lc code=start
class Solution
{
public:
    /**
     * s = "abbb"  p = "a*"
     *       i           j
     */
    bool isMatch(string s, string p)
    {
        //             / dfs(i  , j-2)  if p[j] == "*"                                       // 并未使用 "c*"
        // dfs(i, j) =   dfs(i-1, j  )  if p[j] == "*" && (p[j-1] == s[i] || p[j-1] == '.')  // 使用 "c*" 或 ".*"
        //             \ dfs(i-1, j-1)  if p[j] == "." || p[j] == s[i]                       // 使用 "."  或 字符可以匹配
        int len_s = s.size(), len_p = p.size();

        vector<vector<bool>> f(len_s + 1, vector<bool>(len_p + 1, false));
        // init s = "" && p = "" is true
        f[0][0] = true;
        // init s = "" && p = "a%b%c%"
        for (int j = 0; j < len_p; j++)
        {
            if (p[j] == '*')
                f[0][j + 1] = f[0][j - 1];
        }

        for (int i = 0; i < len_s; i++)
            for (int j = 0; j < len_p; j++)
            {
                if (p[j] == '*')
                {
                    // dfs(i, j-2) 并未使用 "c*"
                    f[i + 1][j + 1] = f[i + 1][j + 1] || f[i + 1][j - 1];

                    if (s[i] == p[j - 1] || p[j - 1] == '.')
                        // dfs(i-1, j) 持续匹配多个 c
                        f[i + 1][j + 1] = f[i + 1][j + 1] || f[i][j + 1];
                }
                else if (p[j] == '.' || p[j] == s[i])
                    // dfs(i-1, j-1) 使用 "."  或 字符可以匹配
                    f[i + 1][j + 1] = f[i + 1][j + 1] || f[i][j];
            }

        return f[len_s][len_p];
    }
};
// @lc code=end
