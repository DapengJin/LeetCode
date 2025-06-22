#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=523 lang=cpp
 *
 * [523] 连续的子数组和
 */

// @lc code=start
class Solution
{
public:
    bool checkSubarraySum(vector<int> &nums, int k)
    {
        // 同余定理：对于任意整数 m, n，
        // 若 (n - m) 能被 k 整除，则有 n % k == m % k。
        // ⇔ 如果前缀和 sum[j] 和 sum[i] 对 k 取模相同，
        //    那么 (sum[j] - sum[i]) % k == 0，
        //    即子数组 nums[i+1..j] 的和能被 k 整除。

        // r2i: 记录每个前缀和对 k 取模后的余数 r，
        //      对应在数组中最早出现该余数的位置 i。
        unordered_map<int, int> r2i; // {remainder, index}
        // init r2i[0] = -1
        r2i[0] = -1;

        int n = nums.size();
        int r = 0; // 当前前缀和对 k 取模的结果

        for (int i = 0; i < n; i++)
        {
            // 更新前缀和余数
            r = (r + nums[i]) % k;

            // 如果这个余数之前出现过
            if (r2i.contains(r))
            {
                if (i - r2i[r] >= 2) // 且 长度 大于等于 2
                    return true;

                continue; // 不要更新 余数 已经存在的 index
            }
            else
                r2i[r] = i;
        }

        return false;
    }
};
// @lc code=end
