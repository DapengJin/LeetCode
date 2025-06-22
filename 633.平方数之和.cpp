#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=633 lang=cpp
 *
 * [633] 平方数之和
 */

// @lc code=start
/*
问：为什么 a^2 + b^2 < c 时，可以把 a 加一？不会错过答案吗？

答：不会错过。我们使用的是双指针的方式，a 从 0 开始递增，b 从 sqrt(c) 开始递减。

当 a^2 + b^2 < c 时，说明当前的组合不够大。我们希望让 a^2 + b^2 增大以逼近 c。

此时，如果我们固定 a，不断减小 b，比如从 b 到 b - 1, b - 2, ..., 那么 b^2 会减小，
而 a^2 是固定的，所以整个 a^2 + b^2 会进一步变小，离 c 越来越远。

也就是说，在 a 固定的情况下，不存在更大的 b′（b′ ≤ b）的组合能满足 a^2 + b′^2 == c。

因此，我们可以安全地增大 a，让 a^2 变大，从而让 a^2 + b^2 变大，继续寻找可能的组合。
*/
class Solution
{
public:
    bool judgeSquareSum(int c)
    {
        int a = 0, b = sqrt(c);

        while (a <= b)
        {
            if (a * a < c - b * b)
                a++;
            else if (a * a > c - b * b)
                b--;
            else
                return true;
        }

        return false;
    }
};
// @lc code=end

/*  */
class Solution
{
public:
    bool judgeSquareSum(int c)
    {
        // a = sqrt(c - b*b)
        // 2 * a * a = c 这是 a 的最大值
        int n = sqrt(c / 2);

        for (int a = 0; a <= n; a++)
        {
            int b = sqrt(c - a * a);
            if (b * b + a * a == c) return true;
        }

        return false;
    }
};
