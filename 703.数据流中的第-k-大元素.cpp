#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=703 lang=cpp
 *
 * [703] 数据流中的第 K 大元素
 */

// @lc code=start
class KthLargest {
    priority_queue<int, vector<int>, greater<int>> q; // min_heap
    int k; 
public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (auto x: nums)
            add(x); 
    }
    
    int add(int val) {
        q.push(val); 

        if (q.size() > k) q.pop(); 

        return q.top(); 
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
// @lc code=end

