#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=474 lang=cpp
 *
 * [474] 一和零
 */

// @lc code=start
class Solution
{
public:
    int findMaxForm(vector<string> &strs, int m, int n)
    {
        int l = strs.size();

        vector cnt(l, vector<int>(2, 0));

        for (int i = 0; i < l; i++)
        {
            for (auto c : strs[i])
            {
                if (c == '0')
                    cnt[i][0]++;
                else
                    cnt[i][1]++;
            }
        }
        
        // f[i][j][k] = max(f[i-1][j][k], f[i-1][j-cnt[i][0]][k-cnt[i][1]] + 1)

        vector f(l + 1, vector(m + 1, vector<int>(n + 1, 0)));

        for (int i = 0; i < l; i++)
            for (int j = 0; j < m + 1; j++)
                for (int k = 0; k < n + 1; k++)
                    if (j - cnt[i][0] >= 0 && k - cnt[i][1] >= 0)
                        f[i + 1][j][k] = max(f[i][j][k], f[i][j - cnt[i][0]][k - cnt[i][1]] + 1);
                    else
                        f[i + 1][j][k] = f[i][j][k];

        return f[l][m][n];
    }
};
// @lc code=end
