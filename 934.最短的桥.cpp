#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=934 lang=cpp
 *
 * [934] 最短的桥
 */

// @lc code=start
class Solution
{
public:
    vector<int> dir{-1, 0, 1, 0, -1};

    void dfs(vector<vector<int>> &grid, queue<pair<int, int>> &i1, int x, int y)
    {
        if (x < 0 || x >= grid.size() ||
            y < 0 || y >= grid[0].size() ||
            grid[x][y] != 1)
            return;

        // mark the first island to 2
        grid[x][y] = 2;
        i1.push({x, y});

        for (int i = 0; i < 4; i++)
        {
            dfs(grid, i1, x + dir[i], y + dir[i + 1]);
        }
    }

    int shortestBridge(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        bool first_island = false;
        queue<pair<int, int>> q;

        // find the first island
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1)
                {
                    first_island = true;
                    dfs(grid, q, i, j);
                    break;
                }

            if (first_island == true)
                break;
        }

        // find the shorest path for all points in i1
        int count = q.size(), level = 0;

        while (count != 0)
        {
            while (count--)
            {
                auto [r, c] = q.front();
                q.pop();

                for (int i = 0; i < 4; i++)
                {
                    int x = r + dir[i], y = c + dir[i + 1];

                    if (0 <= x && x < m &&
                        0 <= y && y < n)
                    {
                        if (grid[x][y] == 0)
                        {
                            grid[x][y] = 2;
                            q.push({x, y});
                        }
                        else if (grid[x][y] == 1)
                        {
                            return level;
                        }
                    }
                }

                // !!! wrong place!
                // level++;
            }

            level++;
            count = q.size();
        }

        return level;
    }
};
// @lc code=end
