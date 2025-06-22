#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=784 lang=cpp
 *
 * [784] 字母大小写全排列
 */

// @lc code=start
class Solution
{
public:
    vector<string> letterCasePermutation(string s)
    {
        int n = s.size();
        string c = s;
        vector<string> res;

        /* 选不选 */
        // function<void(int)> dfs = [&](int i)
        // {
        //     if (i == n)
        //     {
        //         res.push_back(c);
        //         return; // !!! 记得return
        //     }

        //     dfs(i + 1);

        //     if (isalpha(s[i]))
        //     {
        //         c[i] = c[i] ^ ' ';
        //         dfs(i + 1);
        //         c[i] = c[i] ^ ' '; // !!! 变回 s[i] 要 c[i] 取反
        //     }
        // };

        /* 选第几个 */
        function<void(int)> dfs = [&](int i)
        {
            res.push_back(c);

            for (int j = i; j < n; j++)
            {
                if (isalpha(c[j]))
                {
                    c[j] ^= ' ';
                    dfs(j + 1);
                    c[j] ^= ' ';
                }
            }
        };

        dfs(0);

        return res;
    }
};
// @lc code=end
