#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=583 lang=cpp
 *
 * [583] 两个字符串的删除操作
 */

// @lc code=start
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        string &s = word1, &t = word2;

        int m = s.size(), n = t.size();

        vector f(m + 1, vector(n + 1, 0));

        // f[0][0] = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (i == 0)
                    f[i][j + 1] = j + 1; // init
                if (j == 0)
                    f[i + 1][j] = i + 1; // init

                if (s[i] == t[j])
                    f[i + 1][j + 1] = f[i][j];
                else
                    f[i + 1][j + 1] = min(f[i][j + 1], f[i + 1][j]) + 1;
            }

        return f[m][n];
    }
};
// @lc code=end
