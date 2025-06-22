#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=415 lang=cpp
 *
 * [415] 字符串相加
 */

// @lc code=start
/**
 * follow-up: 当输入 包含小数部分的字符串数字
 */
class Solution
{
public:
    string addStrings(string num1, string num2)
    {
        int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
        string res = "";

        while (i >= 0 || j >= 0 || carry)
        {
            if (i >= 0)
                carry += num1[i--] - '0';
            if (j >= 0)
                carry += num2[j--] - '0';

            res.push_back('0' + carry % 10);

            carry = carry / 10;
        }

        ranges::reverse(res);

        return res;
    }
};
// @lc code=end
class Solution1
{
public:
    string addStrings(string num1, string num2)
    {
        // 确保都有小数点
        if (num1.find('.') == string::npos) num1 += '.';
        if (num2.find('.') == string::npos) num2 += '.';

        auto dot1 = num1.find('.');
        auto dot2 = num2.find('.');

        // 补齐小数位
        while (num1.size() - dot1 < num2.size() - dot2) num1 += "0";
        while (num1.size() - dot1 > num2.size() - dot2) num2 += "0";

        int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
        string res;

        while (i >= 0 || j >= 0 || carry)
        {
            // 处理小数点，直接跳过并添加
            if (i >= 0 && num1[i] == '.')
            {
                i--;
                j--;
                res += '.';
                continue;
            }

            // 累加当前位数字与进位
            if (i >= 0) carry += num1[i--] - '0';
            if (j >= 0) carry += num2[j--] - '0';

            res.push_back('0' + carry % 10);

            carry = carry / 10;
        }

        // 反转结果字符串（因为我们是从低位往高位加的）
        ranges::reverse(res);

        // 去除小数部分末尾多余的 0（如 .500 → .5）
        while (res.back() == '0') res.pop_back(); 
        if (res.back() == '.') res.pop_back(); 

        return res;
    }
};