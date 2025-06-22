#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=63 lang=cpp
 *
 * [63] 不同路径 II
 */

// @lc code=start
class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        // dp
        // f[i][j] = f[i-1][j] + f[i][j-1]
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();

        vector f(m + 1, vector(n + 1, 0));
        // init f[0][1] = 1;
        f[0][1] = 1;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (obstacleGrid[i][j] == 0)
                    f[i + 1][j + 1] = f[i + 1][j] + f[i][j + 1];
            }

        return f[m][n];
    }
};
// @lc code=end
