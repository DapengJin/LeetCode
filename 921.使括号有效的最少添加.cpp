#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=921 lang=cpp
 *
 * [921] 使括号有效的最少添加
 */

// @lc code=start
class Solution {
public:
    int minAddToMakeValid(string s) {
        int openCount = 0, missingRightParentheses = 0;
    
        for (char c : s) {
            if (c == '(') {
                openCount++;
            } else { // c == ')'
                if (openCount > 0) {
                    openCount--;  // 匹配一个 '('
                } else {
                    missingRightParentheses++;  // 需要额外加一个 '('
                }
            }
        }
    
        return openCount + missingRightParentheses;
    }
};
// @lc code=end

