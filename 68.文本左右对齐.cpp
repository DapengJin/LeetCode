#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=68 lang=cpp
 *
 * [68] 文本左右对齐
 */

// @lc code=start
class Solution
{
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth)
    {
        vector<string> result;
        int n = words.size();
        int index = 0;

        while (index < n)
        {
            int totalChars = words[index].size();
            int last = index + 1; // 范围：[index, last)

            // 贪心放尽可能多的词
            while (last < n && totalChars + 1 + words[last].size() <= maxWidth)
            {
                totalChars += 1 + words[last].size(); // +1 for space
                last++;
            }

            int gaps = last - index - 1;
            string line;

            // 最后一行或该行只有一个单词：左对齐
            if (last == n || gaps == 0)
            {
                for (int i = index; i < last; ++i)
                {
                    line += words[i];
                    if (i < last - 1)
                        line += " ";
                }
                line += string(maxWidth - line.size(), ' ');
            }
            else
            {
                // 两端对齐
                int totalSpaces = maxWidth - (totalChars - gaps);
                int spacePerGap = totalSpaces / gaps;
                int extraSpaces = totalSpaces % gaps;

                for (int i = index; i < last - 1; ++i)
                {
                    line += words[i];
                    line += string(spacePerGap + (i - index < extraSpaces ? 1 : 0), ' ');
                }
                line += words[last - 1]; // 最后一个单词不需要空格
            }

            result.push_back(line);
            index = last;
        }

        return result;
    }
};
// @lc code=end
