#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=8 lang=cpp
 *
 * [8] 字符串转换整数 (atoi)
 */

// @lc code=start
class Automation
{
    string state = "start";

    unordered_map<string, vector<string>> table =
        {
            //           ' '      '+/-'     number    other
            {"start", {"start", "signed", "number", "end"}},
            {"signed", {"end", "end", "number", "end"}},
            {"number", {"end", "end", "number", "end"}},
            {"end", {"end", "end", "end", "end"}}};

    int get_col(char c)
    {
        if (isspace(c))
            return 0;
        else if (c == '+' || c == '-')
            return 1;
        else if (isdigit(c))
            return 2;
        else
            return 3;
    }

public:
    int sign = 1;
    long long res = 0;

    void get(char c)
    {
        state = table[state][get_col(c)];

        if (state == "number")
        {
            res = res * 10 + c - '0';
            res = sign == 1 ? min(res, (long long)INT_MAX) : min(res, -(long long)INT_MIN);
        }
        else if (state == "signed")
            sign = c == '+' ? 1 : -1;
    }
};

class Solution
{
public:
    int myAtoi(string s)
    {
        Automation a;

        for (auto c : s)
        {
            a.get(c);
        }

        return a.sign * a.res;
    }
};
// @lc code=end
class Solution
{
public:
    int myAtoi(string s)
    {
        int n = s.size(), i = 0;
        // 1. 跳过空格
        while (i < n && s[i] == ' ')
            i++;
        if (i >= n)
            return 0; // **空串或全空格** 直接返回 0

        // 2. 处理符号
        bool neg = false;
        if (s[i] == '-' || s[i] == '+')
        {
            neg = (s[i] == '-');
            i++;
        }

        // 3. 读数字并实时 clamp
        long long res = 0;
        while (i < n && isdigit(s[i]))
        {
            res = res * 10 + (s[i] - '0');
            if (!neg && res >= INT_MAX)
                return INT_MAX;
            if (neg && res >= (long long)INT_MAX + 1)
                return INT_MIN;
            i++;
        }

        // 4. 返回结果
        return neg ? -(int)res : (int)res;
    }
};