#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=13 lang=cpp
 *
 * [13] 罗马数字转整数
 */

// @lc code=start
class Solution
{
public:
    int romanToInt(string s)
    {
        unordered_map<char, int> dict{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
        int n = s.size();
        int res = 0;

        for (int i = 0; i < n; i++)
        {
            if (i + 1 < n && dict[s[i]] < dict[s[i + 1]])
                res -= dict[s[i]];
            else
                res += dict[s[i]];
        }

        return res;
    }
};
// @lc code=end
