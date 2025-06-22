#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=139 lang=cpp
 *
 * [139] 单词拆分
 */

// @lc code=start
class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        s = " " + s;
        int n = s.length();

        vector<bool> dp(n, false);
        dp[0] = true;

        for (int i = 1; i <= n; i++)
            for (auto word : wordDict)
            {
                int m = word.size();

                if (i >= m && s.substr(i - m + 1, m) == word)
                    dp[i] = dp[i - m];

                if (dp[i])
                    break;
            }

        return dp[n - 1];
    }
};
// @lc code=end
