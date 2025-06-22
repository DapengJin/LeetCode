#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1458 lang=cpp
 *
 * [1458] 两个子序列的最大点积
 */

// @lc code=start
class Solution
{
public:
    int maxDotProduct(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size(), n = nums2.size();

        // f[i][j] = max(f[i-1][j], f[i][j-1], f[i-1][j-1] + nums[i] * nums[j])
        vector f(m + 1, vector(n + 1, INT_MIN / 2)); 
        // init all 0 !!! 是错的 !!!
        // 如果一个都可以不选 那初始化为 0 可以
        // 要是必须有一个 就得 初始化为 -inf 然后 把 点积 加到 状态转移方程 中

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                int v = nums1[i] * nums2[j];

                f[i + 1][j + 1] = ranges::max({f[i][j + 1], f[i + 1][j], f[i][j] + v, v});
            }

        return f[m][n];
    }
};
// @lc code=end
