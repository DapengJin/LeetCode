#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=43 lang=cpp
 *
 * [43] 字符串相乘
 */

// @lc code=start
class Solution
{
public:
    string multiply(string num1, string num2)
    {
        // 任一数字为0，结果必然为"0"
        if (num1 == "0" || num2 == "0")
        {
            return "0";
        }

        string ans = "0"; // 最终答案初始化为0
        int m = num1.size(), n = num2.size();

        // 从 num2 的最低位开始逐位乘
        for (int i = n - 1; i >= 0; i--)
        {
            string curr;   // 存储当前位乘积的字符串
            int carry = 0; // 进位

            // 补零：相当于乘法时个位、十位、百位对齐（低位补0）
            for (int j = n - 1; j > i; j--)
            {
                curr.push_back(0); // 用占位数，后面转成字符
            }

            int y = num2.at(i) - '0'; // 当前位的数字

            // num2 的当前位和 num1 的每一位做乘法
            for (int j = m - 1; j >= 0; j--)
            {
                int x = num1.at(j) - '0';
                int product = x * y + carry;
                curr.push_back(product % 10); // 当前位
                carry = product / 10;         // 更新进位
            }

            // 如果还有进位，继续加进来
            while (carry != 0)
            {
                curr.push_back(carry % 10);
                carry /= 10;
            }

            // 当前乘法结果为逆序，需要翻转为正序
            reverse(curr.begin(), curr.end());

            // 每一位数字加上 '0' 变成字符
            for (auto &c : curr)
            {
                c += '0';
            }

            // 累加当前乘积到总和中
            ans = addStrings(ans, curr);
        }

        return ans;
    }

    // 字符串加法（大数相加），两个字符串倒序逐位相加
    string addStrings(string &num1, string &num2)
    {
        int i = num1.size() - 1, j = num2.size() - 1, add = 0;
        string ans;

        while (i >= 0 || j >= 0 || add != 0)
        {
            int x = i >= 0 ? num1.at(i) - '0' : 0;
            int y = j >= 0 ? num2.at(j) - '0' : 0;
            int result = x + y + add;
            ans.push_back(result % 10); // 当前位
            add = result / 10;          // 进位
            i--;
            j--;
        }

        // 结果翻转回正序
        reverse(ans.begin(), ans.end());

        // 数字转字符
        for (auto &c : ans)
        {
            c += '0';
        }

        return ans;
    }
};
// @lc code=end
