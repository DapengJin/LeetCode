#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=52 lang=cpp
 *
 * [52] N 皇后 II
 */

// @lc code=start
class Solution
{
public:
    int totalNQueens(int n)
    {
        int res = 0;
        vector<int> is_col(n), diag1(2 * n - 1), diag2(2 * n - 1);

        function<void(int)> dfs = [&](int r)
        {
            if (r == n)
            {
                res++;
                return;
            }

            for (int c = 0; c < n; c++)
            {
                int r_minus_c = r - c + n - 1;

                if (!is_col[c] && !diag1[r + c] && !diag2[r_minus_c])
                {
                    is_col[c] = diag1[r + c] = diag2[r_minus_c] = true;
                    dfs(r + 1);
                    is_col[c] = diag1[r + c] = diag2[r_minus_c] = false;
                }
            }
        };

        dfs(0);
        return res;
    }
};
// @lc code=end
