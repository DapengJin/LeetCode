#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=162 lang=cpp
 *
 * [162] 寻找峰值
 */

// @lc code=start
class Solution
{
public:
    int findPeakElement(vector<int> &nums)
    {
        int n = nums.size(); 
        // 蓝色代表 peak 或 peak 右边
        int l = -1, r = n - 1; // 最后一个元素 n-1 必定是蓝色, 
                               // 所以最后一个元素是不用分类的

        while (l + 1 < r)
        { 
            int mid = l - (l - r) / 2 ; 

            if (nums[mid] > nums[mid+1]) // 蓝
                r = mid; 
            else 
                l = mid; 
        }

        return r;
    }
};
// @lc code=end
