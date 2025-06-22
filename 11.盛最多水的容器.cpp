#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */

// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        /**
         * 设定两个指针，分别指向数组的头和尾
         * 若两指针的高度不同，移动高度较大的指针，不可能使面积增大，（不管那个指针移动多少步）
         *      因为移动高度较大的指针，宽度减小，（若指针指向更大的高度，其整体高度还是由另一个矮的指针决定的）
         *      高度不变或减小，面积不可能增大
         * 所以，移动高度较小的指针
         */
        int n = height.size(), res = 0, l = 0, r = n - 1;

        while (l < r) 
        {
            res = max(res, min(height[l], height[r]) * (r - l));

            if (height[l] < height[r]) 
                l++; 
            else 
                r--;
        }

        return res; 

    }
};
// @lc code=end

