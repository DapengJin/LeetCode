#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=31 lang=cpp
 *
 * [31] 下一个排列
 */

// @lc code=start
class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        int n = nums.size();

        // 示例输入：[1, 3, 5, 4, 2]

        // 第一步：从后往前找，第一个违反递增顺序的数 nums[i] （3）
        // 即找到第一个 nums[i] < nums[i+1]，准备与右侧更大的数交换
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1])
        {
            i--;
        }

        // 如果找到了，进入第二步；否则跳过第二步，反转整个数组
        if (i >= 0)
        {
            // 第二步：从后往前找，第一个 nums[i] > nums[j] （4）
            int j = n - 1;
            while (nums[j] <= nums[i])
                j--;

            // 交换 nums[i] 和 nums[j]，使整体稍大 （因为选的是最小的数）
            swap(nums[i], nums[j]); // [1, 4, 5, 3, 2]
        }

        // 第三步：反转 nums[i+1:]（如果上面跳过第二步，此时 i = -1）
        // 已经变大了 后面要尽可能小
        reverse(nums.begin() + i + 1, nums.end()); // [5, 3, 2] => [2, 3, 5]
    }
};
// @lc code=end
