#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=14 lang=cpp
 *
 * [14] 最长公共前缀
 */

// @lc code=start
class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        if (!strs.size())
        {
            return "";
        }

        string str0 = strs[0]; // use strs[0] as string to compare

        for (int i = 0; i < str0.size(); i++)
        {
            char c = str0[i];

            for (int j = 1; j < strs.size(); j++) // start from 1
            {
                string &str = strs[j];

                if (i >= str.size() || str[i] != c)
                    return str0.substr(0, i);
            }
        }

        return str0;
    }
};
// @lc code=end
