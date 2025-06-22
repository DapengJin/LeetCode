#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=166 lang=cpp
 *
 * [166] 分数到小数
 */

// @lc code=start
class Solution
{
public:
    string fractionToDecimal(int numerator, int denominator)
    {
        if (numerator == 0)
            return "0"; // 特判：0除什么都是0

        string result;

        // 如果结果是负数，加上负号
        if ((numerator < 0) ^ (denominator < 0))
            result += "-";

        // 转成 long long，避免溢出
        long long rem = llabs((long long)numerator);   // remainder
        long long div = llabs((long long)denominator); // divisor

        // 整数部分
        result += to_string(rem / div);
        rem %= div; // 取余，准备做小数部分

        if (rem == 0)
            return result; // 没有小数，直接返回

        result += "."; // 有小数部分

        // 记录每个余数第一次出现的位置，用来判断循环
        unordered_map<long long, int> remPos;

        while (rem != 0)
        {
            if (remPos.count(rem))
            {
                // 出现循环了：在之前的位置插入 '('，末尾加 ')'
                result.insert(remPos[rem], "(");
                result += ")";
                break;
            }

            // 记录当前余数在 result 中的位置
            remPos[rem] = result.size();

            rem *= 10;
            result += to_string(rem / div);
            rem %= div;
        }

        return result;
    }
};
// @lc code=end
