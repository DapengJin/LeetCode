#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=712 lang=cpp
 *
 * [712] 两个字符串的最小ASCII删除和
 */

// @lc code=start
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        string &s = s1, &t = s2;

        int m = s.size(), n = t.size();

        vector f(m + 1, vector(n + 1, 0));

        // f[0][0] = 0;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (i == 0)
                    f[i][j + 1] = f[i][j] + t[j]; // init
                if (j == 0)
                    f[i + 1][j] = f[i][j] + s[i]; // init

                if (s[i] == t[j])
                    f[i + 1][j + 1] = f[i][j];
                else
                    f[i + 1][j + 1] = min(f[i][j + 1] + s[i], f[i + 1][j] + t[j]);
            }

        return f[m][n];
    }
};
// @lc code=end

