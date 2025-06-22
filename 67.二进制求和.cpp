#include "pkgs.h"
/*
 * @lc app=leetcode.cn id=67 lang=cpp
 *
 * [67] 二进制求和
 */

// @lc code=start
class Solution {
public:
    string addBinary(string a, string b) {
        ranges::reverse(a);
        ranges::reverse(b);
        string res;
        int m = a.size(), n = b.size(); 
        int i = 0, carry = 0; 
        
        while (i < m || i < n || carry )
        { 
            if (i < m) carry += a[i] - '0'; 
            if (i < n) carry += b[i] - '0'; 

            res.push_back((carry % 2) + '0'); 
            carry = carry / 2; 
            i++; 
        }

        ranges::reverse(res);
        return res;
    }
};
// @lc code=end

