#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=518 lang=cpp
 *
 * [518] 零钱兑换 II
 */

// @lc code=start
class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        int n = coins.size();

        // f[i][c] = f[i-1][c] + f[i][c-nums[i]]
        // i+1
        // 和答案无关的转移可能会溢出，从而报错
        // 为了避免报错，使用 unsigned
        vector f(n + 1, vector<unsigned>(amount + 1));

        // init all 0, f[0][0] = 1
        f[0][0] = 1;

        for (int i = 0; i < n; i++)
        {
            for (int c = 0; c <= amount; c++)
            {
                if (c < coins[i])
                {
                    f[i + 1][c] = f[i][c];
                }
                else
                {
                    f[i + 1][c] = f[i][c] + f[i + 1][c - coins[i]];
                }
            }
        }

        return f[n][amount];
    }
};
// @lc code=end
