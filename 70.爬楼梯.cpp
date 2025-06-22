#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 */

// @lc code=start
class Solution {
public:
    int climbStairs(int n) {
        // f[0]=1, f[1]=1
        vector<int> dp(n+1, 1); 

        for (int i = 2; i<= n ; i++)
            dp[i] = dp[i-1] + dp[i-2];
        
        return dp[n];
    }
};
// @lc code=end

