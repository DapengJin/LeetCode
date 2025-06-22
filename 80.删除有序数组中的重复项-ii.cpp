#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=80 lang=cpp
 *
 * [80] 删除有序数组中的重复项 II
 */

// @lc code=start
class Solution
{
public:
    // Stack
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size();
        int stack_size = 2; // 栈的大小，前两个元素默认保留

        for (int i = 2; i < n; i++)
            if (nums[i] != nums[stack_size - 2]) // 和栈顶下方的元素比较
                nums[stack_size++] = nums[i];    // 入栈

        return min(stack_size, n);
    }
};
// @lc code=end
