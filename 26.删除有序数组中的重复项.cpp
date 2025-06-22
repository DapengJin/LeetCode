#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=26 lang=cpp
 *
 * [26] 删除有序数组中的重复项
 */

// @lc code=start
class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int writer = 1, n = nums.size();

        for (auto x : nums)
        {
            // 如果当前 x 和之前 writer 写过的数字不一样
            // writer 就应该写新数了
            if (x != nums[writer - 1])
            {
                nums[writer] = x;
                writer++;
            }
        }

        return writer;
    }
};
// @lc code=end
