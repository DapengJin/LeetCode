#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=81 lang=cpp
 *
 * [81] 搜索旋转排序数组 II
 */

// @lc code=start
class Solution
{
public:
    bool search(vector<int> &nums, int target)
    {
        int n = nums.size(), l = 0, r = n - 1, mid;

        while (l <= r)
        {
            mid = l + (r - l) / 2;

            if (nums[mid] == target)
                return true;

            // [mid, r] is sorted
            if (nums[mid] < nums[r])
                // target is inside
                if (nums[mid] < target && nums[r] >= target)
                    l = mid + 1;
                else
                    r = mid - 1;
            // [l, mid] is sorted
            else if (nums[l] < nums[mid])
                // target is inside
                if (nums[l] <= target && nums[mid] > target)
                    r = mid - 1;
                else
                    l = mid + 1;
            /*
            可以替代底下的两个 else if:

            else if (nums[l] == nums[mid] && nums[mid] == nums[r]) {
                ++l;
                --r;
            }
            */

            // !!! cannot tell with part is sorted, but nums[l] is not target
            else if (nums[l] == nums[mid])
                l++;
            // !!! cannot tell with part is sorted, but nums[r] is not target
            else if (nums[mid] == nums[r])
                r--;
        }

        return false;
    }
};
// @lc code=end
