#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 */

// @lc code=start
class Solution
{
public:
    // 选/不选
    vector<string> generateParenthesis(int n)
    {
        int m = n * 2;
        string path(m, 0);
        vector<string> res;

        function<void(int, int)> dfs = [&](int i, int open)
        {
            if (i == m)
                res.push_back(path);

            if (open < n)
            {
                path[i] = '(';
                dfs(i + 1, open + 1);
            }

            if (i - open < open)
            {
                path[i] = ')';
                dfs(i + 1, open);
            }
        };

        dfs(0, 0);

        return res;
    }
    // 选第几个 为左括号
    // vector<string> generateParenthesis(int n)
    // {
    //     vector<string> ans;
    //     vector<int> path; // 记录左括号的下标
    //     // i = 目前填了多少个括号
    //     // balance = 左括号个数 - 右括号个数
    //     auto dfs = [&](this auto &&dfs, int i, int balance)
    //     {
    //         if (path.size() == n)
    //         {
    //             string s(n * 2, ')');
    //             for (int j : path)
    //             {
    //                 s[j] = '(';
    //             }
    //             ans.emplace_back(s);
    //             return;
    //         }
    //         // 枚举填 close=0,1,2,...,balance 个右括号
    //         for (int close = 0; close <= balance; close++)
    //         {
    //             // 先填 close 个右括号，然后填 1 个左括号，记录左括号的下标 i+close
    //             path.push_back(i + close);
    //             dfs(i + close + 1, balance - close + 1);
    //             path.pop_back();
    //         }
    //     };
    //     dfs(0, 0);
    //     return ans;
    // }
};
// @lc code=end
