#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=989 lang=cpp
 *
 * [989] 数组形式的整数加法
 */

// @lc code=start
class Solution
{
public:
    vector<int> addToArrayForm(vector<int> &nums1, int k)
    {
        vector<int> nums2, res;

        while (k)
        {
            nums2.push_back(k % 10);
            k /= 10;
        }

        ranges::reverse(nums1);
        int i = 0, carry = 0;
        int m = nums1.size(), n = nums2.size();

        while (i < m || i < n || carry)
        {
            if (i < m)
                carry += nums1[i];
            if (i < n)
                carry += nums2[i];

            res.push_back(carry % 10);
            carry /= 10;

            i++;
        }

        ranges::reverse(res);

        return res;
    }
};
// @lc code=end
