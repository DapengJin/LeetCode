#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=198 lang=cpp
 *
 * [198] 打家劫舍
 */

// @lc code=start
class Solution
{
public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        // vector<int> cache(n, -1);

        // // @cache
        // function<int(int)> dfs = [&](int idx) -> int
        // {
        //     if (idx < 0)
        //         return 0;

        //     if (cache[idx] != -1) return cache[idx];

        //     int res = max(dfs(idx - 1), dfs(idx - 2) + nums[idx]);

        //     cache[idx] = res;

        //     return res;
        // };

        // return dfs(n - 1);

        vector<int> f(n + 2, 0);

        for (int i = 0; i < n; i++)
        {
            // new_f = max(f1      , f0   + nums[i]); // 常数空间优化
            f[i + 2] = max(f[i + 1], f[i] + nums[i]);
            // f0 = f1; 
            // f1 = new_f;
        }

        return f[n + 1]; // return f1; 
    }
};
// @lc code=end
class Solution1
{
public:
    int rob(vector<int> &nums)
    {
        // !!! 添加一个dummy node节省边界思考
        /*
        int n = nums.size();

        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums [1]);

        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums [1]);

        for (int i = 2; i < n; i++)
        {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[n - 1];
        */

        int n = nums.size();
        vector<int> dp(n + 2, 0);

        for (int i = 0; i < n; i++)
            dp[i + 2] = max(dp[i + 1], dp[i] + nums[i]);

        return dp[n + 1];
    }
};