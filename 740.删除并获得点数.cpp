#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=740 lang=cpp
 *
 * [740] 删除并获得点数
 */

// @lc code=start
class Solution
{
    int rob(vector<int> &nums)
    {
        int n = nums.size();

        int f0 = 0;
        int f1 = 0;

        for (int x : nums)
        {
            int new_f = max(f0 + x, f1);

            f0 = f1;
            f1 = new_f;
        }

        return f1;
    }

public:
    int deleteAndEarn(vector<int> &nums)
    {
        int mx = ranges::max(nums);
        vector<int> a(mx + 1);

        for (auto x : nums)
            a[x] += x;

        return rob(a);
    }
};
// @lc code=end
