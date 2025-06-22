#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=695 lang=cpp
 *
 * [695] 岛屿的最大面积
 */

// @lc code=start
#define NEW_AREA(i, j)                                \
    do                                                \
    {                                                 \
        local_area++;                                 \
        /* set new area to be 0 to avoid duplacate */ \
        grid[i][j] = 0;                               \
        island.push({i, j});                          \
    } while (0)

class Solution
{
public:
    int dfs(vector<vector<int>> &grid, int r, int c)
    {
        if (r < 0 || r >= grid.size() ||
            c < 0 || c >= grid[0].size() ||
            grid[r][c] == 0)
            return 0;

        grid[r][c] = 0;

        return 1 +
               dfs(grid, r + 1, c) +
               dfs(grid, r - 1, c) +
               dfs(grid, r, c + 1) +
               dfs(grid, r, c - 1);
    }
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int res = 0, m = grid.size(), n = grid[0].size();

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                res = max(res, dfs(grid, i, j));

        return res;
    }

    int maxAreaOfIsland1(vector<vector<int>> &grid)
    {
        vector<int> dir{-1, 0, 1, 0, -1};

        int m = grid.size(), n = grid[0].size(), res = 0;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    // init
                    stack<pair<int, int>> island;
                    int local_area = 0;
                    // find new area
                    NEW_AREA(i, j);

                    // DFS
                    while (!island.empty())
                    {
                        auto [r, c] = island.top();
                        island.pop();

                        for (int k = 0; k < 4; k++)
                        {
                            int x = r + dir[k], y = c + dir[k + 1];

                            if (0 <= x && x < m &&
                                0 <= y && y < n &&
                                grid[x][y] == 1)
                            {
                                NEW_AREA(x, y);
                            }
                        }
                    }

                    res = max(res, local_area);
                }
            }
        }

        return res;
    }
};
// @lc code=end
