#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1004 lang=cpp
 *
 * [1004] 最大连续1的个数 III
 */

// @lc code=start
/* sliding window */
class Solution
{
public:
    /* 滑动窗口 */
    int longestOnes(vector<int> &nums, int k)
    {
        int res = 0, l = 0, cnt = 0; // 当前窗口中 0 的个数

        for (int r = 0; r < nums.size(); r++)
        {
            if (nums[r] == 0)
                cnt++;

            // 当窗口中 0 的数量超过 k 时，需要收缩左边界
            while (cnt > k)
            {
                if (nums[l] == 0)
                    cnt--;

                l++;
            }

            res = max(res, r - l + 1);
        }

        return res;
    }

    /* follow up: the array is a circular array */
    int longestOnes_circular(vector<int> &nums, int k)
    {
        int res = 0, l = 0, cnt = 0;

        for (int r = 0; r < nums.size() * 2; r++)
        {
            if (nums[r % 2] == 0)
                cnt++;

            while (cnt > k)
            {
                if (nums[l % 2] == 0)
                    cnt--;

                l++;
            }

            res = max(res, r - l + 1);
        }

        return res;
    }

    /* follow up: -1 cannot be connected */
    int longestOnes_minus1(vector<int> &nums, int k)
    {
        int res = 0, l = 0, cnt = 0;

        for (int r = 0; r < nums.size(); r++)
        {
            if (nums[r] == 0)
                cnt++;
            else if (nums[r] == -1)
            {
                cnt = 0; 
                l = r + 1; 
                continue;
            }

            while (cnt > k)
            {
                if (nums[l] == 0)
                    cnt--;

                l++;
            }

            res = max(res, r - l + 1);
        }

        return res;
    }
};
// @lc code=end
