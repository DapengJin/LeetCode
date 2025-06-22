#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=2698 lang=cpp
 *
 * [2698] 求一个整数的惩罚数
 */

// @lc code=start
int PRE_SUM[1001];

/**
 * int init = []() { ... }(); 
 * 是一个 C++ Lambda 表达式 的用法，
 * 它结合了 Lambda 表达式 和 立即调用（Immediately Invoked Function Expression, IIFE）
 * 的特性。
 * 
 * 为什么 PRE_SUM 没有被显式捕获？
 *	这个 PRE_SUM 是 全局变量，它并不是局部变量或者是某个函数内部的局部状态。
 *  因为 PRE_SUM 是全局的，它是可以在 Lambda 表达式内直接访问的，无需显式捕获。
 */
int init = []()
{
    for (int i = 1; i <= 1000; i++)
    {
        string s = to_string(i * i);
        int n = s.size();

        // 分割 s，看 能不能 加起来得到 i
        function<bool(int, int)> dfs = [&](int p, int sum)
        {
            if (p == n)
                return sum == i;

            int x = 0;

            for (int j = p; j < n; j++)
            {
                x = x * 10 + s[j] - '0';

                if (dfs(j + 1, sum + x))
                    return true;
            }

            return false;
        };

        PRE_SUM[i] = PRE_SUM[i - 1] + (dfs(0, 0) ? i * i : 0);
    }

    return 0; 
}();

class Solution
{
public:
    int punishmentNumber(int n)
    {
        return PRE_SUM[n];
    }
};
// @lc code=end
