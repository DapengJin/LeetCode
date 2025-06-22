#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=33 lang=cpp
 *
 * [33] 搜索旋转排序数组
 */

// @lc code=start
class Solution
{
public:
        /**
         * 蓝色 代表 target 及 其右侧，如何找到蓝色
         * 
         * case1           / mid
         *                /
         *               / target
         *              /
         *                          end
         *                        /
         *                       /   
         *                      /
         *     mid > end 
         *         target > end && target <= mid 
         * 
         * ------------------------------------------------
         * 
         * case2           / 
         *                /
         *               / target
         *              /
         *                          end
         *                        / mid
         *                       / 
         *                      / target
         *     mid <= end
         *         target > end || target <= mid  
        */
    int search(vector<int> &nums, int target)
    {
        int n = nums.size();
        int end = nums[n - 1];

        // 蓝色 代表 target 及 其右侧
        auto is_blue = [&](int mid) -> bool
        {
            int mid_val = nums[mid];

            if (mid_val > end)            // 第二种情况 第 1 段
                return target  > end &&   // target 也在同一段
                       mid_val >= target; // 满足 蓝色的定义
            else                          // 第一种情况 或 的二种情况 第 2 段
                return target  > end ||   // target 在第 1 段
                       mid_val >= target; // target 也在同一段 && 满足 蓝色的定义
        };

        int l = -1, r = n; 

        while (l+ 1 < r){ 
            int mid = l - (l - r) / 2; 

            if (is_blue(mid))
                r = mid;
            else
                l = mid;
        }

        if (r == n || nums[r] != target) 
            return -1; 

        return r; 
    }
};
// @lc code=end
