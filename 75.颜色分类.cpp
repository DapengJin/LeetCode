#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=75 lang=cpp
 *
 * [75] 颜色分类
 */

// @lc code=start
class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        int n = nums.size();
        int p0 = 0, p2 = n - 1; // p0 指向下一个 0 应该放的位置，p2 指向下一个 2 应该放的位置

        for (int i = 0; i <= p2; ++i)
        { // 遍历到 p2 为止
            while (i <= p2 && nums[i] == 2)
            {
                swap(nums[i], nums[p2]); // 如果当前是 2，交换到后面去
                --p2;                    // 缩小 2 的区域
            }
            if (nums[i] == 0)
            {
                swap(nums[i], nums[p0]); // 如果当前是 0，交换到前面去
                ++p0;                    // 扩大 0 的区域
            }
            
            // 如果是 1，不动，i 自然前进
        }
    }
};
// @lc code=end
