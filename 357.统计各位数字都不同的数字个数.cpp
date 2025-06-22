#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=357 lang=cpp
 *
 * [357] 统计各位数字都不同的数字个数
 */

// @lc code=start
class Solution
{
public:
    int countNumbersWithUniqueDigits(int n)
    {

        int res = 0;
        vector<int> used(10);

        function<void(int)> dfs = [&](int idx)
        {
            res++;

            if (idx == n)
                return;

            for (int j = 0; j < 10; j++)
            {
                if (!used[j])
                {
                    if (idx == 0 && j == 0) // !!!
                        continue; // no heading 0
                        
                    used[j] = true;
                    dfs(idx + 1);
                    used[j] = false;
                }
            }
        };

        dfs(0);

        return res;
    }
};
// @lc code=end
