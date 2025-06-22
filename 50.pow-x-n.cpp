/*
 * @lc app=leetcode.cn id=50 lang=cpp
 *
 * [50] Pow(x, n)
 */

// @lc code=start
// 快速幂
/**
 * x^13
 * 
 * 13 = 1101
 * 
 * 1    0    1    1
 * x   x^2  x^4  x^8 
 */
class Solution
{
public:
    double myPow(double x, int N)
    {
        double ans = 1;
        long long n = N;

        if (n < 0) // x^-n = (1/x)^n
        {
            n = -n;
            x = 1 / x;
        }

        while (n) // 从低到高枚举 n 的每个比特位
        {
            if (n & 1)    // 这个比特位是 1
                ans *= x; // 把 x 乘到 ans 中

            x *= x;  // x 自身平方
            n >>= 1; // 继续枚举下一个比特位
        }

        return ans;
    }
};
// @lc code=end
