#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=503 lang=cpp
 *
 * [503] 下一个更大元素 II
 */

// @lc code=start
class Solution
{
public:
    vector<int> nextGreaterElements(vector<int> &nums)
    {
        int n = nums.size();
        stack<int> s;
        vector<int> res(n, -1);

        for (int i = 0; i < 2 * n; i++)
        {
            while (!s.empty() && nums[i % n] > nums[s.top()])
            {
                res[s.top()] = nums[i % n];
                s.pop();
            }

            s.push(i % n);
        }

        return res;
    }
};
// @lc code=end
