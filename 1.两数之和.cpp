#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> dict({{nums[0], 0}});  // {val : idx}
        int n = nums.size(); 

        for (int i = 1; i < n; i++)
        { 
            int x = target - nums[i]; 

            if (dict.contains(x)) return {dict[x], i}; 

            dict[nums[i]] = i; 
        }

        return {}; 
    }
};
// @lc code=end

