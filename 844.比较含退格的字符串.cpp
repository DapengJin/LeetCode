#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=844 lang=cpp
 *
 * [844] 比较含退格的字符串
 */

// @lc code=start
class Solution
{
public:
    string newString(string ss)
    {
        int slow = 0;

        for (int fast = 0; fast < ss.length(); fast++)
        {
            if (ss[fast] != '#')
            {
                ss[slow] = ss[fast];
                slow++;
            }
            else if (slow > 0)
                slow--;
        }

        ss.resize(slow);
        
        return ss;
    }

    bool backspaceCompare(string s, string t)
    {
        return newString(s) == newString(t);
    }
};
// @lc code=end
