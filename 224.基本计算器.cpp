#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=224 lang=cpp
 *
 * [224] 基本计算器
 */

// @lc code=start
class Solution {
    int parse(string &s, int &i)
    { 
        char op = '+'; 
        int num = 0, n = s.size() ;
        vector<int> st; 

        for (; i < n; i++)
        { 
            char c = s[i]; 

            // 1. 累积数字字符到 num
            if (isdigit(c))
                num = num * 10 + (c - '0'); 

            // 2. 遇到 '('，进入递归子表达式
            if (c == '(') 
                num = parse(s, ++i); 

            // 3. 当遇到操作符、'(' 或到达末尾时 [')' 也算到达末尾]，结算 num
            if (!isdigit(c) && c != ' ' || i == n-1)
            { 
                if      (op == '+') st.push_back( num); 
                else if (op == '-') st.push_back(-num); 

                num = 0; 
                op = c; 
            }

            // 4. 到达末尾，跳出循环
            if (c == ')') break; 
        }

        // 结算 stack 里所有值
        return accumulate(st.begin(), st.end(), 0); 
    }
public:
    int calculate(string s)
    {
        int i = 0;
        return parse(s, i); 
    }
};
// @lc code=end
class Solution
{
public:
    int calculate(string s)
    {
        // 栈 ops 用来保存 “当前上下文的符号”（+1 或 -1），即遇到 '(' 时将当前 sign 入栈，
        // 遇到 ')' 时再出栈恢复到上一层
        stack<int> ops;
        int n = s.size(), i = 0, sign = 1, res = 0;

        ops.push(1);

        while (i < n)
        {
            if (s[i] == ' ') // 跳过空格
                i++;
            else if (s[i] == '+') // 遇到 '+'，当前符号设为栈顶（上层符号作用下的 +）
            {
                sign = ops.top();
                i++;
            }
            else if (s[i] == '-')
            {
                sign = -ops.top();
                i++;
            }
            else if (s[i] == '(') // 遇到 '('，将当前 sign 入栈，开启新一层计算
            {
                ops.push(sign);
                i++;
            }
            else if (s[i] == ')') // 遇到 ')'，结束当前层，出栈恢复到上一层的符号上下文
            {
                ops.pop();
                i++;
                sign = ops.top(); // 这里也不用 没有 ) 后面不接 符号的情况
            }
            else // 处理连续的数字字符，构造完整数字
            {
                long num = 0;
                while (i < n && s[i] >= '0' && s[i] <= '9')
                {
                    num = num * 10 + s[i] - '0';
                    i++;
                }

                res += sign * num;
            }
        }

        return res;
    }
};