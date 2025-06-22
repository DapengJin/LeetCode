#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=746 lang=cpp
 *
 * [746] 使用最小花费爬楼梯
 */

// @lc code=start
class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        // cost dfs(i)
        // {
        //     if i <= 1
        //         return 0;

        //     return min(dfs(i-1) + cost[i-1], dfs(i-2) + cost[i-2]);
        // }

        int n = cost.size();
        vector<int> f(n+1);

        for (int i = 2; i < n+1; i++)
        {
            f[i] = min(f[i - 1]+ cost[i-1], f[i - 2]+ cost[i-2]) ;
        }

        return f[n];
    }
};
// @lc code=end
