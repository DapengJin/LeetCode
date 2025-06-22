#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2850 lang=cpp
 *
 * [2850] 将石头分散到网格图的最少移动次数
 */

// @lc code=start
class Solution
{
public:
    int minimumMoves(vector<vector<int>> &grid)
    {
        vector<pair<int, int>> from, to;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j])
                    for (int k = 1; k < grid[i][j]; k++)
                        from.push_back({i, j});
                else // grid[i][j] is 0
                    to.push_back({i, j});
            }

        int n = from.size();
        int res = INT_MAX;

        // function<void(int)> dfs = [&](int idx)
        // {
        //     if (idx == n)
        //     {
        //         int count = 0;

        //         for (int i = 0; i < n; i++)
        //         {
        //             count += abs(from[i].first  - to[i].first) +
        //                      abs(from[i].second - to[i].second);
        //         }

        //         res = min(res, count);
        //         return;
        //     }

        //     for (int j = idx; j < n; j++)
        //     {
        //         swap(from[idx], from[j]);
        //         dfs(idx + 1);
        //         swap(from[idx], from[j]);
        //     }
        // };

        // dfs(0);

        /* 全排列 */
        do
        {
            int count = 0;

            for (int i = 0; i < n; i++)
            {
                count += abs(from[i].first - to[i].first) +
                         abs(from[i].second - to[i].second);
            }

            res = min(res, count);
        } while (next_permutation(from.begin(), from.end()));

        return res;
    }
};
// @lc code=end