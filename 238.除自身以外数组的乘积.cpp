#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=238 lang=cpp
 *
 * [238] 除自身以外数组的乘积
 */

// @lc code=start
class Solution
{
public:
    /**
     * 不使用额外空间
     * 先计算 suf，然后一边计算 pre，一边把 pre 直接乘到 suf[i] 中。最后返回 suf。
     * 
     * 题目说「输出数组不被视为额外空间」，所以该做法的空间复杂度为 O(1)。
     *      此外，这种做法比上面少遍历了一次。
     * 
     */
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> pre(n, 1);
        for (int i = 1; i < n; i++)
        {
            pre[i] = pre[i - 1] * nums[i - 1];
        }

        vector<int> suf(n, 1);
        for (int i = n - 2; i >= 0; i--)
        {
            suf[i] = suf[i + 1] * nums[i + 1];
        }

        vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            ans[i] = pre[i] * suf[i];
        }
        return ans;
    }
};
// @lc code=end
