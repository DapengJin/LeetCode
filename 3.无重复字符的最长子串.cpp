#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 */

// @lc code=start
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_set<char> set;
        int n = s.size(), l = 0, res = 0;

        for (int r = 0; r < n; r++)
        {
            // if the right char is in the set, shrink the the window until the char is gone.
            while (set.contains(s[r]))
            {
                char c = s[l++];
                set.erase(c);

                if (c == s[r]) break;
            }

            set.emplace(s[r]);
            res = max(res, (int)set.size());
        }

        return res; 
    }
};
// @lc code=end
