/*
 * @lc app=leetcode.cn id=2507 lang=cpp
 *
 * [2507] 使用质因数之和替换后可以取到的最小值
 * 
 * https://www.bilibili.com/video/BV1LW4y1T7if/
 */

// @lc code=start
class Solution
{
public:
    int smallestValue(int n)
    {
        /**
         * 1. n 怎么变？ 
         *      n 不会变大
         *      n = a * (n/a) 最大情况就是 a = 2， s = 2 + n/2 (if n/2 为质数)
         * 2. 得出 s <= n 
         *      => 不断循环 直到 质因数之和 等于 n 为止
         */
        while (true) 
        {
            int i = 2, x = n, s = 0; 

            while (i * i <= x)
            {
                while (x % i == 0)
                {
                    x = x / i;
                    s = s + i;
                }

                i++;
            }

            if (x != 1) 
                s = s + x; 

            if (s == n) return s ; 

            n = s; 
        }

    }
};
// @lc code=end
