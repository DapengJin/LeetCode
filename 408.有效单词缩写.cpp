#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=408 lang=cpp
 *
 * [408] 有效单词缩写
 *
字符串可以用 缩写 进行表示，缩写 的方法是将任意数量的 不相邻 的子字符串替换为相应子串的长度。例如，字符串 "substitution" 可以缩写为（不止这几种方法）：

"s10n" ("s ubstitutio n")
"sub4u4" ("sub stit u tion")
"12" ("substitution")
"su3i1u2on" ("su bst i t u ti on")
"substitution" (没有替换子字符串)
下列是不合法的缩写：

"s55n" ("s ubsti tutio n"，两处缩写相邻)
"s010n" (缩写存在前导零)
"s0ubstitution" (缩写是一个空字符串)
给你一个字符串单词 word 和一个缩写 abbr ，判断这个缩写是否可以是给定单词的缩写。

子字符串是字符串中连续的非空字符序列。



示例 1：

输入：word = "internationalization", abbr = "i12iz4n"
输出：true
解释：单词 "internationalization" 可以缩写为 "i12iz4n" ("i nternational iz atio n") 。
示例 2：

输入：word = "apple", abbr = "a2e"
输出：false
解释：单词 "apple" 无法缩写为 "a2e" 。


提示：

1 <= word.length <= 20
word 仅由小写英文字母组成
1 <= abbr.length <= 10
abbr 由小写英文字母和数字组成
abbr 中的所有数字均符合 32-bit 整数范围
 */

// @lc code=start
class Solution
{
public:
    bool validWordAbbreviation(string word, string abbr)
    {
        int i = 0, j = 0; // i 遍历 word，j 遍历 abbr

        while (i < word.size() && j < abbr.size())
        {
            if (isdigit(abbr[j]))
            {
                if (abbr[j] == '0')
                    return false; // 前导零非法

                int num = 0;

                while (j < abbr.size() && isdigit(abbr[j]))
                {
                    num = num * 10 + (abbr[j++] - '0');
                }

                i += num; // 跳过 num 个字符
            }
            else
            {
                if (word[i] != abbr[j])
                    return false;
                    
                i++;
                j++;
            }
        }

        // 双指针都必须正好走到末尾
        return i == word.size() && j == abbr.size();
    }
};
// @lc code=end
class Solution
{
public:
    bool validWordAbbreviation(string word, string abbr)
    {
        int len = (int)abbr.length();     // 记录缩写字符串的长度
        int wordLen = (int)word.length(); // 记录原始单词的长度
        int abbrLen = 0, num = 0;         // abbrLen: 计算展开后的缩写长度; num: 存储当前解析出的数字

        for (int i = 0; i < len; ++i)
        {
            if (abbr[i] >= 'a' && abbr[i] <= 'z') // 当前字符是字母
            {
                abbrLen += num + 1; // 将前面解析出的数字 num 加入总长度，并加上当前字母
                num = 0;            // 重置 num，因为新的字母出现

                // 如果展开长度超出 word 长度，或者字符不匹配，返回 false
                if (abbrLen > wordLen || abbr[i] != word[abbrLen - 1])
                {
                    return false;
                }
            }
            else // 当前字符是数字
            {
                if (num == 0 && abbr[i] == '0') // 不能出现前导零
                    return false;

                num = num * 10 + (abbr[i] - '0'); // 计算当前完整的数字
            }
        }

        // 最后检查：展开后的长度 + 剩余的 num 应该等于 word 的长度
        return abbrLen + num == wordLen;
    }
};