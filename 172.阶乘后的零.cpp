/*
 * @lc app=leetcode.cn id=172 lang=cpp
 *
 * [172] 阶乘后的零
 */

// @lc code=start
class Solution
{
public:
    int trailingZeroes(int n)
    {
        /**
         * [1,n] 中 5 的倍数有 n1 =⌊5/n⌋ 个，这些数至少贡献出了 n1 个质因子 5。
         * 5^2 的倍数有 n2 =⌊n/5^2⌋ 个，由于这些数已经是 5 的倍数了，
         * 为了不重复统计 5 的个数，我们仅考虑额外贡献的质因子个数，
         * 即这些数额外贡献了至少 n2 个质因子 5。
         */
        return n == 0 ? 0 : n / 5 + trailingZeroes(n / 5);
    }
};
// @lc code=end
