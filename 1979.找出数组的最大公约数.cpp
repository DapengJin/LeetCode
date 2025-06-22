#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1979 lang=cpp
 *
 * [1979] 找出数组的最大公约数
 */

// @lc code=start
class Solution
{
public:
    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
    int findGCD(vector<int> &nums)
    {
        int min_ = INT_MAX, max_ = INT_MIN;

        for (auto num : nums)
        {
            if (num > max_)
                max_ = num;
            if (num < min_)
                min_ = num;
        }

        return gcd(min_, max_);
    }
};
// @lc code=end

// int xGCD(int a, int b, int &x, int &y)
// {
//     if (b == 0)
//     {
//         x = 1, y = 0;
//         return a;
//     }
//     int x_inner, y_inner;
//     int gcd = xGCD(b, a % b, x_inner, y_inner);
//     x = y_inner, y = x_inner - (a / b) * y_inner;
//     return gcd;
// }
