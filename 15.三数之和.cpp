#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=15 lang=cpp
 *
 * [15] 三数之和
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> res;

        ranges::sort(nums);

        for (int i = 0; i < n - 2; i++)
        {
            int x = nums[i];

            if (i && x == nums[i - 1])
                continue;  // 跳过重复数字

            // x 和他后面俩数（最小俩数）加起来都 > 0，在后面就更没可能
            if (x + nums[i + 1] + nums[i + 2] > 0) break; // 优化一
            // x 和最大俩数 加起来都 < 0，x 是没可能了，x 的下一个数再试试
            if (x + nums[n - 2] + nums[n - 1] < 0) continue; // 优化二

            int l = i + 1, r = n - 1;

            while (l < r)
            {
                int s = x + nums[l] + nums[r];

                if (s > 0)
                    r--;
                else if (s < 0)
                    l++;
                else // 三数之和 == 0
                {
                    res.push_back({x, nums[l], nums[r]});
                    for (l++; l < r && nums[l] == nums[l-1]; l++); // 跳过重复数字
                    for (r--; l < r && nums[r] == nums[r+1]; r--); // *2
                }
            }
        }

        return res;
    }
};
// @lc code=end
