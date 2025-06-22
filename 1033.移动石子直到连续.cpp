#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1033 lang=cpp
 *
 * [1033] 移动石子直到连续
 */

// @lc code=start
class Solution
{
public:
    /**
     *  假设 a,b,c 是有序的（从小到大）。
     *
     *  最大移动次数：a 和 c 向 b 靠拢，每次只移动一个单位长度，答案就是 c−a−2。
     *
     *  最小移动次数：
     *      如果 c−a=2，已经连续，无需移动。
     *      如果 b−a=1 或者 c−b=1，说明有两颗石子已经连续，那么只需移动 1 次另一颗石子。
     *      如果 b−a=2 或者 c−b=2，那么把一颗石子移到另外两颗石子之间，只需移动 1 次移动。
     *      否则，a 移动到 b−1，c 移动到 b+1，一共 2 次移动。
     */
    vector<int> numMovesStones(int a, int b, int c)
    {
        int p[] = {a, b, c};
        sort(p, p + 3);
        a = p[0];
        b = p[1];
        c = p[2];
        return {c - a == 2 ? 0 :                  // 已经连续，无需移动。
                    b - a <= 2 || c - b <= 2 ? 1  // 那么把一颗石子移到另外两颗石子之间，只需移动 1 次移动。
                                             : 2, // a 移动到 b−1，c 移动到 b+1，一共 2 次移动
                c - a - 2};                       // c−a−2
    }
};
// @lc code=end
