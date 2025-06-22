#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=680 lang=cpp
 *
 * [680] 验证回文串 II
 */

// @lc code=start
class Solution
{
    bool is_palindrome(string s, int l, int r)
    {
        while (l < r)
        {
            if (s[l] != s[r])
                return false;

            l++;
            r--;
        }

        return true;
    }

public:
    bool validPalindrome(string s)
    {
        int l = 0, r = s.size() - 1;

        while (l < r)
        {
            if (s[l] != s[r])
                return is_palindrome(s, l, r - 1) ||
                       is_palindrome(s, l + 1, r);

            l++;
            r--;
        }

        return true;
    }
};
// @lc code=end

// follow-up：“允许删除最多 k 个字符，使字符串变为回文”
class Solution {
    bool isValidPalindrome(string& s, int l, int r, int k) {
        while (l < r) {
            if (s[l] != s[r]) {
                if (k == 0) return false;
                // 尝试删左或删右
                return isValidPalindrome(s, l + 1, r, k - 1) ||
                       isValidPalindrome(s, l, r - 1, k - 1);
            }
            l++;
            r--;
        }
        return true;
    }

public:
    bool validPalindrome(string s, int k) {
        return isValidPalindrome(s, 0, s.size() - 1, k);
    }
};