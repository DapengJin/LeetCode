#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=97 lang=cpp
 *
 * [97] 交错字符串
 */

// @lc code=start
class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int l = s1.size(), m = s2.size(), n = s3.size();

        if (l + m != n)
            return false;

        if (l == 0 || m == 0)
        {
            if (l == 0)
                swap(s1, s2);

            for (int i = 0; i < s1.size(); i++)
                if (s1[i] != s3[i])
                    return false;

            return true;
        }

        vector f(l + 1, vector(m + 1, vector(n + 1, false)));

        f[0][0][0] = true;

        for (int k = 0; k < n; k++)
            for (int i = 0; i < l; i++)
                for (int j = 0; j < m; j++)
                {
                    if (i == 0 && s2[j] == s3[k])
                        f[0][j + 1][k + 1] = f[0][j][k]; // init

                    if (j == 0 && s1[i] == s3[k])
                        f[i + 1][0][k + 1] = f[i][0][k]; // init

                    f[i + 1][j + 1][k + 1] = (s3[k] == s1[i] ? f[i][j + 1][k] : false) ||
                                             (s3[k] == s2[j] ? f[i + 1][j][k] : false);
                }

        return f[l][m][n];

        // @cache
        // def dfs(i, j, k): # k 可以有 i 和 j 算出来
        //     if i < 0 and j < 0 and k < 0:
        //         return True
                
        //     return (dfs(i, j - 1, k - 1) if j >= 0 and s2[j] == s3[k] else False) or (
        //             dfs(i - 1, j, k - 1) if i >= 0 and s1[i] == s3[k] else False
        //     )

        // return dfs(l - 1, m - 1, n - 1)
    }
};
// @lc code=end
