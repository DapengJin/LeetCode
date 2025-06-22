#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=416 lang=cpp
 *
 * [416] 分割等和子集
 */

// @lc code=start
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int target = accumulate(nums.begin(), nums.end(), 0); 

        if (target % 2 == 1) return false; 

        int n = nums.size(); 

        target /= 2; 
        
        // f[i][c] = f[i-1][c] || f[i-1][c-nums[i]]
        // f[i+1][c] = f[i][c] || f[i][c-nums[i]]
        vector<int> f(target + 1, false); 
        
        // init f[0][0] = 0
        f[0] = true; 

        for (int i = 0; i < n ; i++)
            for (int j = target; j >= nums[i]; j--)
            { 
                f[j] = f[j] || f[j - nums[i]]; 
            }
    
        return f[target];  
    }
};
// @lc code=end

