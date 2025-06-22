#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=1249 lang=cpp
 *
 * [1249] 移除无效的括号
 */

// @lc code=start
class Solution
{
public:
    string minRemoveToMakeValid(string s)
    {
        int left = 0, n = s.size();

        // 第一遍：标记多余的 ')'
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
            {
                left++;
            }
            else if (s[i] == ')')
            {
                if (left > 0) // 能匹配一个 '('
                    left--;
                else
                    s[i] = '#'; // 没有可匹配的 '(', 标记删除
            }
            // 其它字符（包括数字、字母、空格、符号）都跳过
        }

        // 第二遍：从后向前标记多余的 '('
        for (int i = n - 1; i >= 0 && left > 0; i--)
        {
            if (s[i] == '(')
            {
                s[i] = '#';
                left--;
            }
        }

        // 原地压缩，删除所有标记 '#'
        int write = 0;
        
        for (int i = 0; i < n; i++)
            if (s[i] != '#')
                s[write++] = s[i];

        s.resize(write);
        return s;
    }
};
// @lc code=end
class Solution
{
public:
    string minRemoveToMakeValid(string s)
    {
        vector<int> del; // 需要删除的字符索引（包括多余的 '(' 和 ')'）
        vector<int> stk; // 栈：存放未配对的左括号 '(' 的索引
        int n = s.size();

        for (int i = 0; i < n; i++)
        {
            char c = s[i];

            if (isalpha(c))
                continue;
            else if (c == '(')
                stk.push_back(i);
            else // c == ')'
            {
                if (stk.size())
                    stk.pop_back(); // 有配对的左括号，弹出即可（匹配成功）
                else
                    del.push_back(i); // 没有配对的左括号，记录当前右括号索引为非法
            }
        }

        // [右括号无法配对的位置] + [左括号无法配对的位置]
        del.insert(del.end(), stk.begin(), stk.end()); // del is in order

        int j = 0; // del 指针，用来跳过非法字符
        string res = "";

        for (int i = 0; i < n; i++)
        {
            if (j < del.size() && i == del[j])
            {
                j++; // 当前字符是非法的，跳过它
                continue;
            }

            res += s[i];
        }

        return res;
    }
};