#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=528 lang=cpp
 *
 * [528] 按权重随机选择
 */

// @lc code=start
class Solution {
    
    vector<int> presum; 
public:
    Solution(vector<int>& w) {
        int w_sum = 0;

        for( auto x : w)
        { 
            w_sum += x; 
            presum.push_back(w_sum);
        }
    }
    
    int pickIndex() {
        // w: [1,3,5,7]
        // presum: [1,4,9,16]
        // range : [1,16]
        int weight = rand() % presum.back() + 1; // [1, 16] !!! +1 如果 w 有 等于 0 的情况，就不会选到 0
        return lower_bound(presum.begin(), presum.end(), weight) - presum.begin();  
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
// @lc code=end

