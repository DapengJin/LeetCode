#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1588 lang=cpp
 *
 * [1588] 所有奇数长度子数组的和
 */

// @lc code=start
class Solution
{
public:
    int sumOddLengthSubarrays(vector<int> &arr)
    {
        int res = 0;

        for (int i = 0; i < arr.size(); i++)
        {   
            // 选 0个,0个 -> [i] 
            // 选 0个,2个 -> [i,1,2] 
            // 选 2个,0个 -> [2,1,i]
            // 选 2个,2个 -> [2,1,i,1,2]
            //    ⬇️     ⬇️  |  ⬇️     ⬇️  两边选偶数个数字 + i 构成奇数窗口 2 * 2
            // 3  2  1 +(0) i +(0) 1  2
            // ⬆️    ⬆️      |     ⬆️      两边选奇数个数字 + i 构成奇数窗口 2 * 1
            int left = i + 1, right = arr.size() - i, // i 的左边有多少数，包括不选数 0
                left_even = (left + 1) / 2, right_even = (right + 1) / 2,
                left_odd = left / 2, right_odd = right / 2;
            res += (left_even * right_even + left_odd * right_odd) * arr[i];
        }

        return res;
    }
};
// @lc code=end
