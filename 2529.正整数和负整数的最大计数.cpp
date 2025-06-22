#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2529 lang=cpp
 *
 * [2529] 正整数和负整数的最大计数
 */

// @lc code=start
class Solution
{
public:
    int lower_bound(vector<int> &nums, int target)
    {
        int n = nums.size();
        // () 左开右开
        int l = -1, r = n;

        while (l + 1 < r) // (0, 1) 是空集
        {
            int mid = l + (r - l) / 2;

            if (nums[mid] >= target)
                // r 的右边 都是 >= target 的数
                r = mid;
            else
                l = mid;
        }

        return r; // 此时 l + 1 == r
    }

    int maximumCount(vector<int> &nums)
    {
        int neg = lower_bound(nums, 0); 
        int pos = nums.size() - lower_bound(nums, 1); 

        return max(neg, pos);
    }
};
// @lc code=end
