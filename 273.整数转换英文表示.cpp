#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=273 lang=cpp
 *
 * [273] 整数转换英文表示
 */

// @lc code=start

/**
 * 英文是 3 个 3 个 一组的
 *                      "XXX Billion "  +
 *                      "XXX Million "  +
 *                      "XXX Thousand " +
 *                      "XXX "
 * 
 * 所以 我们需要 一个函数 num2str 去处理分割好的 XXX
 * 
 *                      "X Hundred "  +
 * 
 *                      "-----ty "   \ 
 *                                     or "----teen " 
 *                      "X "         /
 * 
 * 记得处理特殊情况 0 和 后面的 空格
 */
class Solution
{
public:
    vector<string> small = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> medium = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    vector<string> large = {"", "Thousand", "Million", "Billion"};
    string H = "Hundred ";

    string numberToWords(int num)
    {
        if (num == 0)
            return small[0];

        string res = "";

        // 1'000'000'000 三个三个一组
        for (int i = 3, unit = 1e9; i >= 0; i--, unit /= 1000)
        {
            int cur_num = num / unit;

            if (cur_num == 0)
                continue;

            res += num2str(cur_num) + large[i] + " ";

            num %= unit;
        }

        while (res.back() == ' ')
            res.pop_back();

        return res;
    }

    string num2str(int x) // 最大 999 
    {
        string res = "";

        if (x >= 100) // 0-9
        {
            res += small[x / 100] + " " + H;
            x %= 100;
        }
        if (x >= 20)
        {
            res += medium[x / 10] + " ";
            x %= 10;
        }
        if (x != 0)
            res += small[x] + " ";

        return res;
    }
};
// @lc code=end
