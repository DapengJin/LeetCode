#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2787 lang=cpp
 *
 * [2787] 将一个数字表示成幂的和的方案数
 */

// @lc code=start
class Solution
{
public:
    int numberOfWays(int n, int x)
    {
        int MOD = 1000'000'007;
        // nums 含有 所有小于 n 的幂
        vector<int> nums;

        for (int i = 1; i <= n; i++)
        {
            int p = pow(i, x);

            if (p <= n)
            {
                nums.push_back(p);
            }
            else break; 
        }

        int target = n;
        n = nums.size();

        // f[i][j] = f[i-1][j] + f[i-1][j-nums[i]]
        // init f[-1][-1] = 1;
        vector f(n + 1, vector(target + 1, 0));
        f[0][0] = 1;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < target + 1; j++)
            {
                f[i + 1][j] = f[i][j];

                if (j - nums[i] >= 0)
                    f[i + 1][j] = (f[i + 1][j] + f[i][j - nums[i]]) % MOD;
            }

        return f[n][target];
    }
};
// @lc code=end
