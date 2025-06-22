#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2826 lang=cpp
 *
 * [2826] 将三个组排序
 */

// @lc code=start
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        vector<int> g; 

        for (auto x: nums)
        { 
            auto it = ranges::upper_bound(g, x); 

            if (it == g.end())
                g.push_back(x); 
            else
                *it = x;
        }

        return nums.size() - g.size(); 
    }
};
// @lc code=end

