#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 */

// @lc code=start
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size(); 
        deque<int> q; // index
        vector<int> res; 

        for (int i = 0; i< n ; i++ ){
            // 入
            while (!q.empty() && nums[i] > nums[q.back()])
                q.pop_back();

            q.push_back(i); 

            // 出 （超出滑动窗口 k）
            if (i - q.front() >= k)
                q.pop_front(); 

            // 记录答案
            if (i >= k-1) res.push_back(nums[q.front()]);
        }
        
        return res; 
    }
};
// @lc code=end

