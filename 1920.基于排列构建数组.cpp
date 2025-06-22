#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1920 lang=cpp
 *
 * [1920] 基于排列构建数组
 */

// @lc code=start
class Solution
{
public:
    vector<int> buildArray(vector<int> &nums)
    {
        int n = nums.size();
        int N = 1000;

        for (int i = 0; i < n; i++)
            nums[i] += N * (nums[nums[i]] % N); // !!! % N 得到之前的数 不要越界了

        for (int i = 0; i < n; i++)
            nums[i] /= N;

        return nums;
    }
};
// @lc code=end
