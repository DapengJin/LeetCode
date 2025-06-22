#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=643 lang=cpp
 *
 * [643] 子数组最大平均数 I
 */

// @lc code=start
class Solution
{
public:
    /**
     * 灵神：入-更新-出。
     */
    double findMaxAverage(vector<int> &nums, int k)
    {
        int max_s = INT_MIN; // 窗口元素和的最大值
        int s = 0;           // 维护窗口元素和

        for (int i = 0; i < nums.size(); i++)
        {
            s += nums[i]; // 1. 进入窗口

            if (i < k - 1) // 窗口大小不足 k
                continue;

            max_s = max(max_s, s); // 2. 更新答案
            s -= nums[i - k + 1];  // 3. 离开窗口
        }
        return (double)max_s / k;
    }
};
// @lc code=end
