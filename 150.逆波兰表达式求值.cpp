#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=150 lang=cpp
 *
 * [150] 逆波兰表达式求值
 * 
 * Follow up: 如何不用额外空间来实现逆波兰表达式求值？
 *      write 是你的「栈顶指针」
 *      数字就往 tokens[write++] 放
 *      操作符就 --write 两次，计算，结果回写到 tokens[write++]
 *      最终结果在 tokens[0]
 */

// @lc code=start
class Solution
{
public:
    int evalRPN(vector<string> &tokens)
    {
        unordered_map<string, function<int(int, int)>> binary_operations = {
            {"+", [](int a, int b) -> int { return a + b; }},
            {"-", [](int a, int b) -> int { return a - b; }},
            {"*", [](int a, int b) -> int { return a * b; }},
            {"/", [](int a, int b) -> int { return a / b; }},
        };
        unordered_map<string, function<int(int, int)>> unary_operations;
        stack<int> st;
        int n = tokens.size();

        for (auto t : tokens)
        {
            if (binary_operations.contains(t))
            {
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();

                st.push(binary_operations[t](b, a));
            }
            else
                st.push(stoi(t));
        }

        return st.top();
    }
};
// @lc code=end
