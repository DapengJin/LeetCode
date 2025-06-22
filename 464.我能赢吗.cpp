#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=464 lang=cpp
 *
 * [464] 我能赢吗
 */

// @lc code=start
/* 压缩状态 + memo */
class Solution
{
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal)
    {
        // 所有数加起来都没有 desiredTotal 大
        if ((1 + maxChoosableInteger) * (maxChoosableInteger) / 2 < desiredTotal)
            return false;

        unordered_map<int, bool> memo;

        function<bool(int, int)> dfs = [&](int visited, int sum) -> bool
        {
            if (memo.contains(visited))
                return memo[visited];

            for (int i = 0; i < maxChoosableInteger; i++)
            {
                if ((visited >> i) & 1) // 已经使用过了
                    continue;

                if (i + 1 + sum >= desiredTotal ||         // 我选了一个数 已经赢了
                    !dfs(visited | (1 << i), i + 1 + sum)) // 我选了一个数 别人赢不了
                    return memo[visited] = true;
            }

            return memo[visited] = false;
        };

        return dfs(0, 0);
    }
};
// @lc code=end
