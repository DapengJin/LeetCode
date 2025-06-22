#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1039 lang=cpp
 *
 * [1039] 多边形三角剖分的最低得分
 */

// @lc code=start
class Solution
{
public:
    int minScoreTriangulation(vector<int> &values)
    {
        int n = values.size();
        vector f(n, vector<int>(n, 0));

        for (int i = n - 1; i >= 0; i--)
            for (int j = i + 2; j < n; j++)
            {
                f[i][j] = INT_MAX;

                for (int k = i + 1; k < j; k++)
                    f[i][j] = min(f[i][j], f[i][k] + f[k][j] + values[i] * values[j] * values[k]);
            }

        return f[0][n - 1];

        // n = len(values)
        // @cache
        // def dfs(i, j):
        //     if i + 1 == j:  # 不存在第三个点
        //         return 0
        //     res = inf
        //     for k in range(i + 1, j):
        //         res = min(
        //             res, dfs(i, k) + dfs(k, j) + values[i] * values[j] * values[k]
        //         )
        //     return res
        // return dfs(0, n - 1)
    }
};
// @lc code=end
