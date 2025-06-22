#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

// @lc code=start
class Solution
{
public:
    int lower_bound0(vector<int> &nums, int target)
    {
        int n = nums.size();
        // [] 左闭右闭
        int l = 0, r = n - 1; 

        while (l <= r)
        {
            int mid = l + (r - l) / 2;

            if (nums[mid] >= target)
                // r 的右边 都是 >= target 的数
                r = mid - 1;
            else
                l = mid + 1;
        }

        return l; // 此时 r + 1 == l
    }

    int lower_bound1(vector<int> &nums, int target)
    {
        int n = nums.size();
        // [) 左闭右开
        int l = 0, r = n; // n - 1 => n

        while (l < r) // l == r 时 [l, l) 是空集
        {
            int mid = l + (r - l) / 2;

            if (nums[mid] >= target)
                // r 的右边 都是 >= target 的数
                r = mid; // mid - 1 => mid
            else
                l = mid + 1;
        }

        return l; // 此时 r == l
    }

    int lower_bound2(vector<int> &nums, int target)
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

    vector<int> searchRange(vector<int> &nums, int target)
    {
        int start = lower_bound0(nums, target), n = nums.size();

        if (!(start < n && nums[start] == target))
            return {-1, -1};

        int end = lower_bound2(nums, target + 1) - 1;

        return {start, end};
    }
};
// @lc code=end
