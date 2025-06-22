#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=227 lang=cpp
 *
 * [227] 基本计算器 II
 */

// @lc code=start
class Solution
{
public:
    /* *表达式中的所有整数都是非负整数* */
    int calculate(string s)
    {
        char presign = '+';
        int num = 0;
        int n = s.size();
        vector<int> stk;

        for (int i = 0; i < n; i++)
        {
            char c = s[i];

            if (isdigit(c))
                num = num * 10 + (int)(c - '0');

            if (!isdigit(c) && c != ' ' || // 符号 或
                i == n - 1)                // n-1 的时候 要算一下最后结果
            {
                switch (presign)
                {
                case '+':
                    stk.push_back(num);
                    break;
                case '-':
                    stk.push_back(-num);
                    break;
                case '*':
                    stk.back() *= num;
                    break;
                case '/':
                    stk.back() /= num;
                    break;
                }

                num = 0;
                presign = c;
            }
        }

        return accumulate(stk.begin(), stk.end(), 0);
    }
};
// @lc code=end

// O(1) space
class Solution
{
public:
    // 如果第一个数是个 signed integer 就不行了
    int calculate(string s)
    {
        int n = s.size(), i = 0;

        // 读一个整数，自动跳过前导空格
        auto get_num = [&]()
        {
            // 跳过所有空格
            while (i < n && s[i] == ' ')
                i++;
            int num = 0;
            // 读取数字
            while (i < n && isdigit(s[i]))
                num = num * 10 + (s[i++] - '0');

            return num;
        };

        // 先读取第一个数字，初始化 pre（上一次运算的操作数）和 res（结果）
        int pre = get_num();
        int res = pre;

        // 主循环：读取运算符并处理后续的数字
        while (i < n)
        {
            // 跳过运算符前的空格
            while (i < n && s[i] == ' ')
                i++;
            // 读取运算符
            char op = s[i++];
            // 读取下一个操作数
            int cur = get_num();

            if (op == '+')
            {
                // 加法：直接把 cur 加到结果里
                pre = cur;
                res += cur;
            }
            else if (op == '-')
            {
                // 减法：把 -cur 加入结果
                pre = -cur;
                res += pre;
            }
            else if (op == '*')
            {
                // 乘法：先从结果中减去上一次加过的 pre，再更新 pre，然后加回新的 pre
                res -= pre;
                pre = pre * cur;
                res += pre;
            }
            else if (op == '/')
            {
                // 除法：同乘法处理逻辑，保持整数除法向零截断
                res -= pre;
                pre = pre / cur;
                res += pre;
            }
        }

        return res;
    }
};