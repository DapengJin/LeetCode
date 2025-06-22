#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=125 lang=cpp
 *
 * [125] 验证回文串
 */

// @lc code=start
class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0, r = s.size() - 1;

        while (l < r) {
            // 跳过非字母数字字符
            while (l < r && !isalnum(s[l])) l++;
            while (l < r && !isalnum(s[r])) r--;

            // 比较，注意忽略大小写
            if (tolower(s[l]) != tolower(s[r]))
                return false;

            l++;
            r--;
        }

        return true;
    }
};
// @lc code=end

class Solution {
public:
    bool isPalindrome(string s) {
        string sub; 

        for (char c : s)
            if (isalpha(c)) sub.push_back(tolower(c)); 
            else if (isdigit(c)) sub.push_back(c); 

        int l = 0, r = sub.size()-1; 

        while (l < r) { 
            if (sub[l] != sub[r]) return false; 

            l++; r--; 
        }

        return true; 
    }
};