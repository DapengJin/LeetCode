
#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=417 lang=cpp
 *
 * [417] 太平洋大西洋水流问题
 */

// @lc code=start
class Solution
{
public:
    vector<int> dir{-1, 0, 1, 0, -1};

    void dfs(vector<vector<int>> &heights, vector<vector<bool>> &reach, int r, int c)
    {
        if (reach[r][c] == true)
            return;

        reach[r][c] = true;

        for (int i = 0; i < 4; i++)
        {
            int x = r + dir[i], y = c + dir[i + 1];

            if (0 <= x && x < heights.size() &&
                0 <= y && y < heights[0].size() &&
                heights[r][c] <= heights[x][y])
                dfs(heights, reach, x, y);
        }

        return;
    }
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> res;
        vector<vector<bool>> ra(m, vector<bool>(n, false)), rp(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++)
        {
            dfs(heights, ra, i, n - 1);
            dfs(heights, rp, i, 0);
        }

        for (int i = 0; i < n; i++)
        {
            dfs(heights, ra, m - 1, i);
            dfs(heights, rp, 0, i);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (ra[i][j] && rp[i][j])
                    res.push_back({i, j});

        return res;
    }
};
// @lc code=end
