#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=349 lang=cpp
 *
 * [349] 两个数组的交集
 */

// @lc code=start
class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_set st(nums1.begin(), nums1.end());
        vector<int> res;

        for (auto x : nums2)
            if (st.erase(x))
                res.push_back(x);

        return res;
    }
};
// @lc code=end
