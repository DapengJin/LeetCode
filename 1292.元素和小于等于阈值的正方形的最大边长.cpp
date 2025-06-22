#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1292 lang=cpp
 *
 * [1292] 元素和小于等于阈值的正方形的最大边长
 */

// @lc code=start
class Solution
{
public:
    int maxSideLength(vector<vector<int>> &mat, int threshold)
    {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> presum(m + 1, vector<int>(n + 1, 0));

        // presum
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                presum[i + 1][j + 1] = presum[i][j + 1] + presum[i + 1][j] -
                                       presum[i][j] + mat[i][j];

        auto bs = [&](pair<int, int> pos) -> int
        {
            auto [x, y] = pos; // x, y is the upper left conner
            // range of possible length
            int l = 0, r = min(m - x, n - y) + 1, mid;
            // add 1 for presum
            x++;
            y++;
            // a, b is the lower right conner
            int sum, a, b, res;

            do
            {
                mid = l + (r - l) / 2;

                a = x + mid - 1;
                b = y + mid - 1;

                sum = presum[a][b] - presum[x - 1][b] - presum[a][y - 1] +
                      presum[x - 1][y - 1];

                if (sum > threshold)
                    r = mid;
                else
                {
                    res = mid;
                    l = mid + 1;
                }

            } while (l < r);

            return res;
        };

        int res = 0;

        // [i][j] is the upper left conner of the square
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                // use the binary search to find the possible square
                res = max(res, bs({i, j}));

        return res;
    }
};
// @lc code=end
