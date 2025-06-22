#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=279 lang=cpp
 *
 * [279] 完全平方数
 */

// @lc code=start
const int N = 10001;
int f[N + 1];

int init = []
{
    // f[i][c] = min(f[i-1][c],  f[i][c - i*i])
    // f   [c] = min(f     [c],  f   [c - i*i])
    // init 0, inf, inf, ...       ⬆️
    //                          这里需要正序 
    //                          因为是从 i 而不是 i-1转移过来的，需要先更新 i 前面的
    ranges::fill(f, INT_MAX);
    f[0] = 0;

    for (int i = 1; i <= 100; i++)
        for (int j = i * i; j <= N; j++)
            f[j] = min(f[j], f[j - i * i] + 1);

    return 0;
}();

class Solution
{
public:
    int numSquares(int n)
    {
        /* 完全背包 */
        return f[n];

        /* 分割类型 */
        // vector<int> dp(n + 1, INT_MAX);
        // dp[0] = 0;

        // // 1 to n, dp[i] = min( dp[ i - j*j ] ) + 1,
        // //           for j*j from 1 to i
        // for (int i = 1; i <= n; i++)
        //     for (int j = 1; j * j <= i; j++)
        //         dp[i] = min(dp[i], dp[i - j * j] + 1);

        // return dp[n];
    }
};
// @lc code=end
