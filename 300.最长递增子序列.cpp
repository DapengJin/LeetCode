#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=300 lang=cpp
 *
 * [300] 最长递增子序列
 */

// @lc code=start
class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> g;

        for (auto x : nums)
        {
            auto it = ranges::lower_bound(g, x);

            if (it == g.end())
                g.push_back(x);
            else
                *it = x;
        }

        return g.size();
    }

    int lengthOfLIS_DP(vector<int> &nums)
    {
        int n = nums.size();
        vector f(n, 0);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
                if (nums[j] < nums[i])
                    f[i] = max(f[i], f[j]);

            f[i]++; // 需要加上它自己
        }

        return ranges::max(f);
    }

    int lengthOfLIS_dfs(vector<int> &nums)
    {
        int n = nums.size();

        function<int(int)> dfs = [&](int i) -> int
        {
            // 不用添加终止条件也会返回 1
            // if (i == 0)
            //     return 1;

            int res = 0;

            for (int j = 0; j < i; j++)
                if (nums[i] > nums[j])
                    res = max(res, dfs(j));

            return res + 1; // + 1 表示 nums[i]
        };

        int res = 0;

        for (int i = 0; i < n; i++)
            res = max(res, dfs(i)); // 枚举 nums[i] 为子数组结尾的数字

        return res;
    }
};
// @lc code=end