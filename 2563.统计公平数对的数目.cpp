#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2563 lang=cpp
 *
 * [2563] 统计公平数对的数目
 */

// @lc code=start
class Solution
{
public:
    long long countFairPairs(vector<int> &nums, int lower, int upper)
    {
        ranges::sort(nums);
        long long ans = 0;

        for (int j = 0; j < nums.size(); j++) // i 必须在 j 的前面，以防重复计算
        {
            // <= upper-nums[j] 的 nums[i] 的个数 
            auto r = upper_bound(nums.begin(), nums.begin() + j, upper - nums[j]);
            // < lower-nums[j] 的 nums[i] 的个数
            auto l = lower_bound(nums.begin(), nums.begin() + j, lower - nums[j]);

            ans += r - l; // iter - iter
        }
        
        return ans;
    }
};
// @lc code=end
