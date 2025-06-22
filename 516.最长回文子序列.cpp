#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=516 lang=cpp
 *
 * [516] 最长回文子序列
 */

// @lc code=start
class Solution
{
public:
    int longestPalindromeSubseq(string s)
    {
        // int n = s.size();
        // vector f(n, vector<int>(n, 0));

        // for (int j = 0; j < n; j++)
        // {
        //     // !!! 加了这个后不用担心 越界问题
        //     f[j][j] = 1;

        //     for (int i = j-1; i >= 0; i--)
        //         if (s[i] == s[j])
        //             f[i][j] = f[i + 1][j - 1] + 2;
        //         else
        //             f[i][j] = max(f[i + 1][j], f[i][j - 1]);
        // }

        // return f[0][n - 1];

        int n = s.size();
        vector<int> f(n, 0);

        for (int j = 0; j < n; j++)
        {
            // !!! 加了这个后不用担心 越界问题
            f[j] = 1;
            int pre = 0;

            for (int i = j - 1; i >= 0; i--)
            {
                int tmp = f[i];

                if (s[i] == s[j])
                    f[i] = pre + 2;
                else
                    f[i] = max(f[i + 1], f[i]);

                pre = tmp;
            }
        }

        return f[0]; 
    }
};
// @lc code=end
