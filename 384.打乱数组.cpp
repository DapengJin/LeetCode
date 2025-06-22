#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=384 lang=cpp
 *
 * [384] 打乱数组
 */

// @lc code=start

/**
 * 有点像 permutation 的写法
 * 只不过这里是随机选
 * 
 * 选第一个数的概率是 1/n
 * 选第二个数的概率是 (n-1)/n * 1/(n-1) 第一次没选中 * 第二次选中了
 *    ... ... 
 * 
 */
class Solution {
    vector<int> nums;
public:
    Solution(vector<int>& nums): nums(nums) {
        
    }
    
    vector<int> reset() {
        return nums; 
    }
    
    vector<int> shuffle() {
        int n = nums.size(); 
        vector<int> nums1(nums.begin(), nums.end()); 

        for (int i = 0; i < n; i++)
        { 
            int pick = rand() % (n - i); 
            swap(nums1[i + pick], nums1[i]); 
        }

        return nums1;       
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
// @lc code=end

