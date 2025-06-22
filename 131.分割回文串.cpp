#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=131 lang=cpp
 *
 * [131] 分割回文串
 */

// @lc code=start
class Solution
{
public:
    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> res;
        vector<string> vals;
        int n = s.size();

        auto is_pali = [&](int l, int r) -> bool
        {
            while (l < r)
            {
                if (s[l] != s[r])
                    return false;

                l++;
                r--;
            }

            return true;
        };

        /* 解2：从 结果 角度 */
        // function<void(int)> dfs = [&](int i)
        // {
        //     if (i == n)
        //     {
        //         res.push_back(vals);
        //         return;
        //     }

        //     for (int j = i; j < n; j++)
        //     {
        //         if (is_pali(i, j))
        //         {
        //             vals.push_back(move(s.substr(i, j - i + 1))); // move is fast
        //             dfs(j + 1);
        //             vals.pop_back();
        //         }
        //     }
        // };

        // dfs(0);

        /* 解1：从 输入 角度 */
        function<void(int, int)> dfs = [&](int i, int start)
        {
            if (i == n)
            {
                res.push_back(vals);
                return;
            }

            // 不选
            // i == n - 1 的时候 一定要判断下 子串 是不是 回文
            // 所以一定要选
            if (i < n - 1)
                dfs(i + 1, start);

            // 选
            if (is_pali(start, i))
            {
                vals.push_back(s.substr(start, i - start + 1));
                dfs(i + 1, i + 1);
                vals.pop_back();
            }
        };

        dfs(0, 0);

        return res;
    }
};
// @lc code=end
