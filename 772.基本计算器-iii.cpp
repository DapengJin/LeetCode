#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=772 lang=cpp
 *
 * [772] 基本计算器 III
 *
实现一个基本的计算器来计算简单的表达式字符串。

表达式字符串只包含非负整数，算符 +、-、*、/ ，左括号 ( 和右括号 ) 。整数除法需要 向下截断 。

你可以假定给定的表达式总是有效的。所有的中间结果的范围均满足 [-231, 231 - 1] 。

注意：你不能使用任何将字符串作为表达式求值的内置函数，比如 eval() 。



示例 1：

输入：s = "1+1"
输出：2
示例 2：

输入：s = "6-4/2"
输出：4
示例 3：

输入：s = "2*(5+5*2)/3+(6/2+8)"
输出：21


提示：

1 <= s <= 104
s 由整数、'+'、'-'、'*'、'/'、'(' 和 ')' 组成
s 是一个 有效的 表达式
 */

// @lc code=start
#include <vector>
#include <string>
#include <numeric> // std::accumulate
#include <cctype>  // std::isdigit

class Solution
{
public:
    // 入口：计算整个表达式的值
    int calculate(const std::string &s)
    {
        int i = 0;         // 全局索引，用于在字符串中移动
        return eval(s, i); // 调用递归函数处理从 s[0] 开始的表达式
    }

private:
    // 递归计算子表达式，从 s[i] 开始，直到遇到 ')' 或字符串末尾
    int eval(const std::string &s, int &i)
    {
        std::vector<int> stk; // 用 vector 维护按 + - * / 处理后的中间结果
        int num = 0;         // 当前累积的数字
        char op = '+';        // 上一个操作符，初始化为 '+' 方便第一个数字入栈

        // 扫描字符串
        for (; i < (int)s.size(); ++i)
        {
            char c = s[i];
            // 如果是数字，累积到 num
            if (std::isdigit(c))
                num = num * 10 + (c - '0');

            // 如果是左括号，递归计算括号内的子表达式
            if (c == '(')
            {
                ++i;
                num = eval(s, i);
            } // 递归完成后，c 肯定没变， i 指向了 匹配的 ')'

            if ((!std::isdigit(c) && c != ' ') || // 如果遇到 操作符、'('，或
                i == (int)s.size() - 1)           // 已经到达字符串末尾 或 ')'，就结算一次 num
            {
                if      (op == '+') stk.push_back( num);
                else if (op == '-') stk.push_back(-num);
                else if (op == '*') stk.back() *= num;
                else if (op == '/') stk.back() /= num;

                // 更新操作符，重置 num
                // op 可能是'('，它只是个占位，等到下一个有效运算符到来时就被覆盖掉了。
                // 这样设计既简化了逻辑，也不会影响最终的计算结果。
                op = c;
                num = 0;
            }
            // 遇到右括号，则结束本层递归，并到 accumulate 结算
            if (c == ')') break;
        }

        // 将所有中间结果累加，即为当前子表达式的值
        return std::accumulate(stk.begin(), stk.end(), 0);
    }
};
// @lc code=end
