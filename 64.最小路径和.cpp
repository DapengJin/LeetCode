#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=64 lang=cpp
 *
 * [64] 最小路径和
 */

// @lc code=start
class Solution
{
public:
    // 如果 四个方向可移动 怎么办？Dijkstra
    int minPathSum_followup(vector<vector<int>> &grid)
    {
        // 1. priority queue
        // 2. dist[0][0] = grid[0][0], 其他 INT_MAX
        // 3. 每次出最小 cost 的点拓展到 dist

        int m = grid.size(), n = grid[0].size();
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> 
            pq;
        vector dist(m, vector(n, INT_MAX));
        vector dir = {-1, 0, 1, 0, -1};

        dist[0][0] = grid[0][0];
        pq.push({grid[0][0], {0, 0}});

        while (pq.size())
        {
            auto [cost, pos] = pq.top();
            pq.pop();
            int x = pos.first, y = pos.second;

            // 到右下角了
            if (x == m - 1 && y == n - 1)
                return cost;

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dir[i], ny = y + dir[i + 1];

                if (nx < 0 || nx >= m || ny < 0 || ny >= n) // out of range
                    continue;

                int new_cost = cost + grid[nx][ny];

                if (new_cost < dist[nx][ny])
                {
                    dist[nx][ny] = new_cost;
                    pq.push({new_cost, {nx, ny}});
                }
            }
        }

        return -1;
    }

    int minPathSum(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();

        vector f(m + 1, vector<int>(n + 1, INT_MAX));
        f[0][1] = 0; // !!! 可以把 f[0][1] 初始化成 0，这样我们无需单独计算 f[1][1]

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                f[i + 1][j + 1] = min(f[i + 1][j], f[i][j + 1]) + grid[i][j];

        return f[m][n];

        // vector<vector<int>> dp(m, vector<int>(n, 0));

        // for (int i = 0; i < m; i++)
        //     for (int j = 0; j < n; j++)
        //         if (i == 0 && j == 0)
        //             dp[i][j] = grid[i][j];
        //         else if (i == 0)
        //             dp[i][j] = dp[i][j - 1] + grid[i][j];
        //         else if (j == 0)
        //             dp[i][j] = dp[i - 1][j] + grid[i][j];
        //         else
        //             dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];

        // return dp[m - 1][n - 1];
    }
};
// @lc code=end
