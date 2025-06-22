#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=167 lang=cpp
 *
 * [167] 两数之和 II - 输入有序数组
 */

// @lc code=start
class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        int l = 0, r = numbers.size() -1 ;

        while (l < r)
        {
            int s = numbers[l] + numbers[r];

            if (s == target)
                break;
            else if (s > target)
                r--;
            else
                l++;
        }

        return {++l, ++r};
    }
};
// @lc code=end
