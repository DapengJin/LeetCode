#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=504 lang=cpp
 *
 * [504] 七进制数
 */

// @lc code=start
class Solution {
public:
    string convertToBase7(int num) {
        if (num == 0)
            return "0"; 

        string base7; 
        bool is_negative = num < 0; 

        num = abs(num); 

        while (num)
        { 
            int quotient = num / 7, remainder = num % 7;

            base7 = to_string(remainder) + base7; 
            num = quotient;
        }

        return is_negative ? "-" + base7 : base7; 
        
    }
};
// @lc code=end

