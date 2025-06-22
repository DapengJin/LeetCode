#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=28 lang=cpp
 *
 * [28] 找出字符串中第一个匹配项的下标
 */

// @lc code=start
class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        int n = haystack.size(), m = needle.size();

        for (int i = 0; i + m <= n; i++) // 只枚举能放下 needle 长度的位置
        {
            bool flag = true;

            // 遍历 needle 的每一位，逐字符比较
            for (int j = 0; j < m; j++)
            {
                if (haystack[i + j] != needle[j])
                {
                    flag = false;
                    break;
                }
            }

            if (flag)
            {
                return i; // 找到匹配的位置，返回起始下标
            }
        }

        return -1;
    }
};
// @lc code=end
