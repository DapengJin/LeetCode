#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=525 lang=cpp
 *
 * [525] 连续数组
 */

// @lc code=start
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> idx; 
        idx[0] = -1; 
        int n = nums.size(); 
        int pre_sum = 0; 
        int res = 0; 

        for (int i = 0 ; i< n ; i++)
        { 
            pre_sum += nums[i] == 1 ? 1 : -1; 

            if (idx.contains(pre_sum))
                res = max(res, i - idx[pre_sum]); 
            else
                idx[pre_sum] = i; 
        }
        
        return res; 
    }
};
// @lc code=end

