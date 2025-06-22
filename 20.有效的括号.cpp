#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */

// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        // stack
        stack<char> stack; 
        unordered_map<char, char> m = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };

        // open ( { [ put it to the stack
        // close top() 

        for (auto c : s)
        { 
            if (m.contains(c)) // close 
                if (stack.size() && stack.top() == m[c]) // match
                    stack.pop(); 
                else
                    return false; 
            else // open
                stack.push(c); 
        }

        return stack.empty(); 
   }
};
// @lc code=end

