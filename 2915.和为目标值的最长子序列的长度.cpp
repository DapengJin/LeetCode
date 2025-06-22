#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2915 lang=cpp
 *
 * [2915] 和为目标值的最长子序列的长度
 */

// @lc code=start
class Solution
{
public:
    int lengthOfLongestSubsequence(vector<int> &nums, int target)
    {
        int n = nums.size();
        // f[i][c] 表示 nums[0, i] 子序列和是 c 的最大长度
        // f[i][c] = max(f[i-1][c], f[i-1][c-nums[i]] + 1)
        vector f(n + 1, vector(target + 1, INT_MIN)); // !!! 不能初始化为 0
        // init 0
        f[0][0] = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j <= target; j++)
            {
                f[i + 1][j] = f[i][j];

                if (j - nums[i] >= 0)
                    f[i + 1][j] = max(f[i][j], f[i][j - nums[i]] + 1);
            }

        return f[n][target] > 0 ? f[n][target] : -1;
    }
};
// @lc code=end
