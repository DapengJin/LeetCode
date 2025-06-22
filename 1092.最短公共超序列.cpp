#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1092 lang=cpp
 *
 * [1092] 最短公共超序列
 */

// @lc code=start
class Solution
{
public:
    string shortestCommonSupersequence(string str1, string str2)
    {
        string &s = str1, &t = str2;
        int m = s.size(), n = t.size();

        // f[i][j] = min(f[i-1][j] + 1, f[i][j-1] + 1)
        //           f[i-1][j-1] + 1                    if s[i] == t[j]
        vector f(m + 1, vector(n + 1, 0));
        // f[0][0] = 0

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (i == 0)
                    f[0][j + 1] = j + 1; // init
                if (j == 0)
                    f[i + 1][0] = i + 1; // init

                if (s[i] == t[j]) // 最短公共超序列一定包含 s[i]
                    f[i + 1][j + 1] = f[i][j] + 1;
                else // 取更短的组成答案
                    f[i + 1][j + 1] = min(f[i][j + 1], f[i + 1][j]) + 1;
            }

        // 倒推答案
        string res;
        int i = m - 1, j = n - 1;

        while (i >= 0 && j >= 0)
        {
            if (s[i] == t[j]) // 公共超序列一定包含 s[i]
            {
                res += s[i];
                i--;
                j--; // 相当于继续递归 f(i - 1, j - 1)
            }
            else if (f[i + 1][j] < f[i][j + 1]) // 往小的地方走，递归到 f[i + 1][j]
            {
                res += t[j]; // j 的规模缩小了
                j--;
            }
            else
            {
                res += s[i];
                i--;
            }
        }

        ranges::reverse(res);

        return s.substr(0, i + 1) + t.substr(0, j + 1) // 补上前面的递归边界
               +
               res;
    }
};
// @lc code=end
