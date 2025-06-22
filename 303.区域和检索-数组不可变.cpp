#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=303 lang=cpp
 *
 * [303] 区域和检索 - 数组不可变
 */

// @lc code=start
class NumArray {
    vector<int> presum{0}; // all index +1
public:
    NumArray(vector<int>& nums) {
        for (auto x: nums)
            presum.push_back(x + presum.back());
    }
    
    int sumRange(int left, int right) {
        return presum[right + 1] - presum[left]; 
    }
};
// @lc code=end

