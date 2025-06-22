#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=277 lang=cpp
 *
 * [277] 搜寻名人
 */

// @lc code=start
bool knows(int a, int b);

class Solution
{
public:
    int findCelebrity(int n)
    {
        int c = 0; // potential celebrity

        for (int i = 0; i < n; i++)
            if (knows(c, i)) // 如果 c 知道 i， c 就不是
                c = i;       // 如果 c 不知道 i， i 就肯定不是

        for (int i = 0; i < n; i++)
            if (i != c)
                if (!knows(i, c) || knows(c, i))
                    return -1;

        return c;
    }
};
// @lc code=end
