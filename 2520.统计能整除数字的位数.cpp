#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2520 lang=cpp
 *
 * [2520] 统计能整除数字的位数
 */

// @lc code=start
class Solution
{
public:
    int countDigits(int num)
    {
        // 枚举数位
        int x = num, res = 0;

        while (x)
        {
            if (num % (x % 10) == 0)
                res++;
            
            x = x / 10; 
        }

        return res; 
    }
};
// @lc code=end
