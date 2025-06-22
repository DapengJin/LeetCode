/*
 * @lc app=leetcode.cn id=367 lang=cpp
 *
 * [367] 有效的完全平方数
 */

// @lc code=start
class Solution
{
public:
    bool isPerfectSquare(int num)
    {
        long long l = 0, r = (long long)num + 1;

        while (l + 1 < r)
        {
            long long mid = (l + r) / 2;

            if (mid <= num / mid)
                l = mid;
            else
                r = mid;
        }

        return l * l == num;
    }
};
// @lc code=end
