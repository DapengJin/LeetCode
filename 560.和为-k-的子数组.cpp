#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=560 lang=cpp
 *
 * [560] 和为 K 的子数组
 */

// @lc code=start
class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        int res = 0, n = nums.size(), presum = 0;
        unordered_map<int, int> counter{{0, 1}}; // {left : times}

        for (auto x : nums)
        {
            presum += x;
            res += counter[presum - k]; // presum - left = k 
                                        // -> left = presum - k;
            counter[presum]++;
        }

        return res;
    }
};
// @lc code=end
